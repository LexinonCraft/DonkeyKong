#include <memory>

#include "Player.hpp"
#include "../Constants.hpp"
#include "../util/EntityVisitor.hpp"
#include "../Stage.hpp"

Player::Player(Ref ref) :
    BaseEntity(ref),
    state(State::InAir),
    position(100.f, -200.f),
    velocity(0.f, 0.f),
    horizontal_direction(HorizontalDirection::None),
    vertical_direction(VerticalDirection::None),
    shape({constants::PLAYER_WIDTH, constants::PLAYER_HEIGHT}) {
        // origin at the rectangle's centre so `position` is the player's centre
        shape.setOrigin({constants::PLAYER_WIDTH / 2.f, constants::PLAYER_HEIGHT}); // origin at the bottom centre of the rectangle
        shape.setFillColor(sf::Color(200, 100, 100)); // light red, stands out on the girders
        shape.setPosition(position);
}

void Player::update(float dt, Stage &level) {
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

            if (!current_platform->covers_x(position.x)) {
                state = State::InAir;
                break;
            }

                switch (vertical_direction) {
                    case VerticalDirection::Up:
                        {
                            std::shared_ptr<Climbable> ladder = level.get_climbables().find_climbable_up_at(position, constants::PLAYER_WIDTH / 2.f, constants::PLAYER_HEIGHT / 2.f);
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
                            std::shared_ptr<Climbable> ladder = level.get_climbables().find_climbable_down_at(position, constants::PLAYER_WIDTH / 2.f, constants::PLAYER_HEIGHT / 2.f);
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
                const std::shared_ptr<Platform> platform_below = level.get_platforms().find_platform_underneath(position, constants::PLAYER_HEIGHT / 2.f);
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
    }

    if (auto left_boundary = level.get_left_boundary()) {
        if (position.x < *left_boundary) {
            position.x = *left_boundary;
        }
    }
    if (auto right_boundary = level.get_right_boundary()) {
        if (position.x > *right_boundary) {
            position.x = *right_boundary;
        }
    }

    shape.setPosition(position);
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
