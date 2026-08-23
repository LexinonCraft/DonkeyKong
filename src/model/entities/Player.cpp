#include "DK/model/entities/Player.hpp"

#include <algorithm>
#include <memory>

#include <SFML/System/Angle.hpp>

#include "DK/Constants.hpp"
#include "DK/model/PlayerData.hpp"
#include "DK/model/Stage.hpp"
#include "DK/model/util/EntityVisitor.hpp"

Player::Player(Ref ref)
    : BaseEntity(ref), state(State::InAir), position(0.f, 0.f), velocity(0.f, 0.f), horizontal_direction(HorizontalDirection::None),
      vertical_direction(VerticalDirection::None), hammer_time_remaining(0.f), shape({constants::PLAYER_WIDTH, constants::PLAYER_HEIGHT}) {
    // origin at the rectangle's centre so `position` is the player's centre
    shape.setOrigin({constants::PLAYER_WIDTH / 2.f, constants::PLAYER_HEIGHT}); // origin at the bottom centre of the rectangle
    shape.setFillColor(sf::Color(200, 100, 100));                               // light red, stands out on the girders
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
            {
                if (handle_platform_fall_through()) {
                    break;
                }
                last_fall_through_platform = nullptr;

                velocity.x = walking_dir;
                position.y = current_platform->surface_y_at(position.x);
                velocity.y = 0.f;
                y_before_jump = position.y;

                if (!current_platform->covers_x(position.x, constants::PLAYER_WIDTH / 2.f, constants::PLAYER_WIDTH / 2.f) ||
                    !current_platform->is_active()) {
                    const std::shared_ptr<Platform> platform_below = stage.get_platforms().find_platform_underneath(
                        position, constants::PLAYER_WIDTH / 2.f, constants::PLAYER_WIDTH / 2.f, constants::SEAM_SNAP_DISTANCE,
                        last_fall_through_platform);
                    if (platform_below) {
                        enter_platform(platform_below);
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

                if (!has_hammer()) {
                    switch (vertical_direction) {
                        case VerticalDirection::Up:
                            {
                                std::shared_ptr<Climbable> ladder = stage.get_climbables().find_climbable_up_at(
                                    position, constants::PLAYER_WIDTH / 2.f, constants::PLAYER_HEIGHT / 2.f);
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
                                std::shared_ptr<Climbable> ladder = stage.get_climbables().find_climbable_down_at(
                                    position, constants::PLAYER_WIDTH / 2.f, constants::PLAYER_HEIGHT / 2.f);
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
                }
                break;
            }
        case State::InAir:
            velocity.y += constants::GRAVITY * dt;

            if (position.y - y_before_jump > constants::PLAYER_MAX_FALL_HEIGHT) {
                die(stage);
            }

            if (velocity.y > 0.0f) {
                const std::shared_ptr<Platform> platform_below =
                    stage.get_platforms().find_platform_underneath(position, constants::PLAYER_WIDTH / 2.f, constants::PLAYER_WIDTH / 2.f,
                                                                   platform_snap_distance(dt), last_fall_through_platform);
                if (platform_below) {
                    enter_platform(platform_below);
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
        case State::Animated:
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

    hammer_time_remaining = std::max(0.f, hammer_time_remaining - dt);

    shape.setPosition(position);

    if (state == State::OnPlatform || state == State::InAir) {
        if (auto pickable = stage.get_pickables().find_touching_pickable(shape)) {
            switch (pickable->get_type()) {
                case Pickable::Type::Hammer:
                    hammer_time_remaining = constants::HAMMER_DURATION;
                    break;
            }
            pickable->on_picked_up();
        }
    }

    if (auto enemy = stage.get_enemies().find_touching_enemy(shape)) {
        const bool enemy_in_front = facing_right ? enemy->get_position().x >= position.x : enemy->get_position().x <= position.x;
        if (has_hammer() && enemy_in_front) {
            enemy->on_hammer_hit(stage);
        } else {
            die(stage);
        }
    }

    stage.get_jumpables().check_all_jumpables(*this, stage);

    if (state != State::InAir) {
        has_jumped_flag = false;
    }
}

void Player::set_horizontal_direction(HorizontalDirection dir) { horizontal_direction = dir; }

void Player::set_vertical_direction(VerticalDirection dir) { vertical_direction = dir; }

void Player::jump() {
    if (state == State::OnPlatform && !has_hammer()) {
        state = State::InAir;
        velocity.y = -constants::PLAYER_JUMP_SPEED;
        has_jumped_flag = true;
    }
}

const sf::RectangleShape &Player::get_shape() const { return shape; }

void Player::check_referenced_entities() {
    if (handle_destroyed_indirect(current_platform) && state == State::OnPlatform) {
        state = State::InAir;
    }
    if (handle_destroyed_indirect(current_ladder) && state == State::Climbing) {
        state = State::InAir;
    }
}

void Player::accept(EntityVisitor &visitor) { visitor.visit(*this); }

float Player::platform_snap_distance(float dt) const {
    float distance = velocity.y * dt;
    if (distance > constants::PLATFORM_MINIMUM_SNAP_DISTANCE) {
        return distance;
    } else {
        return constants::PLATFORM_MINIMUM_SNAP_DISTANCE;
    }
}

void Player::enter_platform(std::shared_ptr<Platform> platform) {
    state = State::OnPlatform;
    current_platform = platform;
    position.y = current_platform->surface_y_at(position.x);
}

void Player::enter_platform(std::shared_ptr<Platform> platform, float x_pos) {
    position.x = x_pos;
    enter_platform(platform);
}

bool Player::handle_platform_fall_through() {
    if (!current_platform) {
        return false;
    }
    bool fall_through = current_platform->fall_through(std::static_pointer_cast<Player>(shared_from_this()));
    if (fall_through) {
        state = State::InAir;
        velocity.x = 0.f;
        last_fall_through_platform = current_platform;
        return true;
    }
    return false;
}

void Player::die(Stage &stage) { stage.on_player_dying(); }
