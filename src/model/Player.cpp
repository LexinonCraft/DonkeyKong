#include <memory>

#include "Player.hpp"
#include "Constants.hpp"
#include "visitor/EntityVisitor.hpp"
#include "repository/PlatformRepository.hpp"
#include "repository/LadderRepository.hpp"
#include "Level.hpp"

Player::Player(Ref<Entity> ref) :
    Entity(ref),
    state(State::InAir),
    position(100.f, -300.f),
    velocity(0.f, 0.f),
    horizontal_direction(HorizontalDirection::None),
    vertical_direction(VerticalDirection::None),
    shape({constants::PLAYER_WIDTH, constants::PLAYER_HEIGHT}) {
        // origin at the rectangle's centre so `position` is the player's centre
        shape.setOrigin({constants::PLAYER_WIDTH / 2.f, constants::PLAYER_HEIGHT}); // origin at the bottom centre of the rectangle
        shape.setFillColor(sf::Color(200, 100, 100)); // light red, stands out on the girders
        shape.setPosition(position);
}

void Player::update(Level &level, float dt) {
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
                            std::shared_ptr<Ladder> ladder = find_ladder_leading_up(level.get_ladders());
                            if (ladder != nullptr) {
                                state = State::Climbing;
                                current_ladder = ladder;
                                velocity.x = 0.f;
                                velocity.y = climbing_dir;
                            }
                        }
                        break;
                    case VerticalDirection::Down:
                        {
                            std::shared_ptr<Ladder> ladder = find_ladder_leading_down(level.get_ladders());
                            if (ladder != nullptr) {
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
                const std::shared_ptr<Platform> platform_below = find_platform_below(level.get_platforms());
                if (platform_below != nullptr) {
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

void Player::accept(EntityVisitor &visitor) const {
    visitor.visit(*this);
}

const std::shared_ptr<Platform> Player::find_platform_below(const PlatformRepository &platforms) const {
    for (auto it = platforms.begin(); it != platforms.end(); ++it) {
        const std::shared_ptr<Platform> platform = it->second;
        if (platform->covers_x(position.x)) {
            float surface = platform->surface_y_at(position.x);
            if (position.y >= surface && surface >= position.y - constants::PLAYER_HEIGHT / 2.f) {
                return platform;
            }
        }
    }
    return nullptr;
}

const std::shared_ptr<Ladder> Player::find_ladder_leading_up(const LadderRepository &ladders) const {
    for (auto it = ladders.begin(); it != ladders.end(); ++it) {
        const std::shared_ptr<Ladder> ladder = it->second;
        const float x_pos = ladder->get_x_pos();
        if (ladder->get_lower_end()->get_ref().get_id() == current_platform->get_ref().get_id() && x_pos - constants::PLAYER_WIDTH / 2.f <= position.x && position.x <= x_pos + constants::PLAYER_WIDTH / 2.f) {
            return ladder;
        }
    }
    return nullptr;
}

const std::shared_ptr<Ladder> Player::find_ladder_leading_down(const LadderRepository &ladders) const {
    for (auto it = ladders.begin(); it != ladders.end(); ++it) {
        const std::shared_ptr<Ladder> ladder = it->second;
        const float x_pos = ladder->get_x_pos();
        if (ladder->get_upper_end()->get_ref().get_id() == current_platform->get_ref().get_id() && x_pos - constants::PLAYER_WIDTH / 2.f <= position.x && position.x <= x_pos + constants::PLAYER_WIDTH / 2.f) {
            return ladder;
        }
    }
    return nullptr;
}
