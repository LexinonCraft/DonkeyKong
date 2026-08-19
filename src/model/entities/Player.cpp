#include <algorithm>
#include <memory>

#include <SFML/System/Angle.hpp>

#include "Player.hpp"
#include "../../Constants.hpp"
#include "../PlayerData.hpp"
#include "../util/EntityVisitor.hpp"
#include "../Stage.hpp"

Player::Player(Ref ref) :
    BaseEntity(ref),
    state(State::InAir),
    position(100.f, -200.f),
    velocity(0.f, 0.f),
    horizontal_direction(HorizontalDirection::None),
    vertical_direction(VerticalDirection::None),
    hammer_time_remaining(0.f),
    shape({constants::PLAYER_WIDTH, constants::PLAYER_HEIGHT}) {
        // origin at the rectangle's centre so `position` is the player's centre
        shape.setOrigin({constants::PLAYER_WIDTH / 2.f, constants::PLAYER_HEIGHT}); // origin at the bottom centre of the rectangle
        shape.setFillColor(sf::Color(200, 100, 100)); // light red, stands out on the girders
        shape.setPosition(position);
}

void Player::update(float dt, Stage &stage) {
    float walking_dir;
    switch (horizontal_direction) {
        case HorizontalDirection::Left:
            walking_dir = -constants::PLAYER_WALKING_SPEED;
            break;
        case HorizontalDirection::Right:
            walking_dir = constants::PLAYER_WALKING_SPEED;
            break;
        case HorizontalDirection::None:
            walking_dir = 0.0f;
            break;
    }

    float climbing_dir;
    switch (vertical_direction) {
        case VerticalDirection::Up:
            climbing_dir = -constants::PLAYER_CLIMBING_SPEED;
            break;
        case VerticalDirection::Down:
            climbing_dir = constants::PLAYER_CLIMBING_SPEED;
            break;
        case VerticalDirection::None:
            climbing_dir = 0.0f;
            break;
    }

    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    switch (state) {
        case State::OnPlatform:
            velocity.x = walking_dir;
            position.y = current_platform->surface_y_at(position.x);
            velocity.y = 0.f;

            if (!current_platform->covers_x(position.x, platform_h_tolerance_left(), platform_h_tolerance_right())) {
                const std::shared_ptr<Platform> platform_below = stage.get_platforms().find_platform_underneath(position, platform_h_tolerance_left(), platform_h_tolerance_right(), constants::SEAM_SNAP_DISTANCE);
                if (platform_below) {
                    current_platform = platform_below;
                    position.y = current_platform->surface_y_at(position.x);
                } else {
                    state = State::InAir;
                }
                break;
            }

            switch (horizontal_direction) {
                case HorizontalDirection::Left:
                    facing_right = false;
                    break;
                case HorizontalDirection::Right:
                    facing_right = true;
                    break;
                case HorizontalDirection::None:
                    break;
            }

            switch (vertical_direction) {
                case VerticalDirection::Up:
                    {
                        std::shared_ptr<Climbable> ladder = stage.get_climbables().find_climbable_up_at(position, constants::PLAYER_WIDTH / 2.f, constants::PLAYER_HEIGHT / 2.f);
                        if (ladder) {
                            state = State::Climbing;
                            current_ladder = ladder;
                            velocity.x = 0.f;
                            velocity.y = climbing_dir;
                        }
                    }
                    break;
                case VerticalDirection::Down:
                    {
                        std::shared_ptr<Climbable> ladder = stage.get_climbables().find_climbable_down_at(position, constants::PLAYER_WIDTH / 2.f, constants::PLAYER_HEIGHT / 2.f);
                        if (ladder) {
                            state = State::Climbing;
                            current_ladder = ladder;
                            velocity.x = 0.f;
                            velocity.y = climbing_dir;
                        }
                    }
                    break;
                case VerticalDirection::None:
                    break;
            }
            break;
        case State::InAir:
            velocity.y += constants::GRAVITY * dt;

            if (velocity.y > 0.0f) {
                const std::shared_ptr<Platform> platform_below = stage.get_platforms().find_platform_underneath(position, platform_h_tolerance_left(), platform_h_tolerance_right(), platform_snap_distance(dt));
                if (platform_below) {
                    state = State::OnPlatform;
                    current_platform = platform_below;
                    velocity.y = 0.0f;
                    position.y = current_platform->surface_y_at(position.x);
                }
            }
            break;
        case State::Climbing:
            velocity.x = 0.f;
            velocity.y = climbing_dir;

            if (position.y > current_ladder->get_lower_end()->surface_y_at(position.x)) {
                state = State::OnPlatform;
                current_platform = current_ladder->get_lower_end();
                position.y = current_platform->surface_y_at(position.x);
            } else if (position.y < current_ladder->get_upper_end()->surface_y_at(position.x)) {
                state = State::OnPlatform;
                current_platform = current_ladder->get_upper_end();
                position.y = current_platform->surface_y_at(position.x);
            }
            break;
        case State::Dying:
            velocity.x = 0.f;
            velocity.y = 0.f;
            break;
    }

    if (auto left_boundary = stage.get_left_boundary()) {
        if (position.x < *left_boundary) {
            position.x = *left_boundary;
        }
    }
    if (auto right_boundary = stage.get_right_boundary()) {
        if (position.x > *right_boundary) {
            position.x = *right_boundary;
        }
    }

    if (state == State::OnPlatform && horizontal_direction != HorizontalDirection::None) {
        walking_time += dt;
    } else {
        walking_time = 0.0f;
    }

    if (state == State::Climbing) {
        if (vertical_direction != VerticalDirection::None) {
            climbing_time += dt;
        }
    } else {
        climbing_time = 0.0f;
    }

    if (state != State::InAir) {
        has_jumped_flag = false;
    }

    hammer_time_remaining = std::max(0.f, hammer_time_remaining - dt);

    shape.setPosition(position);

    if (auto pickable = stage.get_pickables().find_touching_pickable(shape)) {
        switch (pickable->get_type()) {
            case Pickable::Type::Hammer:
                hammer_time_remaining = constants::HAMMER_DURATION;
                break;
        }
        pickable->on_picked_up();
    }

    if (has_hammer()) {
        if (auto enemy = stage.get_enemies().find_touching_enemy(shape)) {
            enemy->on_hammer_hit();
            stage.get_player_data().add_to_score(constants::HAMMER_BARREL_SCORE);
        }
    } else if (stage.get_enemies().find_touching_enemy(shape)) {
        state = State::Dying;
        stage.on_player_dying();
    }
}

void Player::set_horizontal_direction(HorizontalDirection dir) {
    horizontal_direction = dir;
}

void Player::set_vertical_direction(VerticalDirection dir) {
    vertical_direction = dir;
}

void Player::jump() {
    if (state == State::OnPlatform) {
        state = State::InAir;
        velocity.y = -constants::PLAYER_JUMP_SPEED;
        has_jumped_flag = true;
    }
}

const sf::RectangleShape& Player::get_shape() const {
    return shape;
}

void Player::check_referenced_entities() {
    if (handle_destroyed_indirect(current_platform) && state == State::OnPlatform) {
        state = State::InAir;
    }
    if (handle_destroyed_indirect(current_ladder) && state == State::Climbing) {
        state = State::InAir;
    }
}

void Player::accept(EntityVisitor &visitor) {
    visitor.visit(*this);
}

float Player::platform_h_tolerance_left() const {
    if (velocity.x > 0.f) {
        return constants::PLAYER_WIDTH / 2.f + velocity.x * constants::PLATFORM_H_TOLERANCE_FACTOR;
    } else {
        return constants::PLAYER_WIDTH / 2.f;
    }
}

float Player::platform_h_tolerance_right() const {
    if (velocity.x < 0.f) {
        return constants::PLAYER_WIDTH / 2.f + -velocity.x * constants::PLATFORM_H_TOLERANCE_FACTOR;
    } else {
        return constants::PLAYER_WIDTH / 2.f;
    }
}

float Player::platform_snap_distance(float dt) const {
    float distance = velocity.y * dt;
    if (distance > constants::PLATFORM_MINIMUM_SNAP_DISTANCE) {
        return distance;
    } else {
        return constants::PLATFORM_MINIMUM_SNAP_DISTANCE;
    }
}
