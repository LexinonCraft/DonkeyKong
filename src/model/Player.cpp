#include "Player.hpp"
#include "Constants.hpp"

Player::Player() :
    state(State::InAir),
    current_girder(nullptr),
    current_ladder(nullptr),
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

void Player::update(float dt, const std::vector<Girder>& girders, const std::vector<Ladder>& ladders) {
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
        case State::OnGirder:
            velocity.x = walking_dir;
            position.y = current_girder->surface_y_at(position.x);
            velocity.y = 0.f;

            if (!current_girder->covers_x(position.x)) {
                state = State::InAir;
                break;
            }

            const Ladder *ladder;
            switch (vertical_direction) {
                case VerticalDirection::Up:
                    ladder = find_ladder_leading_up(ladders);
                    if (ladder != nullptr) {
                        state = State::Climbing;
                        current_ladder = ladder;
                        velocity.x = 0.f;
                        velocity.y = climbing_dir;
                    }
                    break;
                case VerticalDirection::Down:
                    ladder = find_ladder_leading_down(ladders);
                    if (ladder != nullptr) {
                        state = State::Climbing;
                        current_ladder = ladder;
                        velocity.x = 0.f;
                        velocity.y = climbing_dir;
                    }
                    break;
                case VerticalDirection::None:
                    break;
            }
            break;
        case State::InAir:
            velocity.y += constants::GRAVITY * dt;

            if (velocity.y > 0.0f) {
                const Girder *girder_below = find_girder_below(girders);
                if (girder_below != nullptr) {
                    state = State::OnGirder;
                    current_girder = girder_below;
                    velocity.y = 0.0f;
                    position.y = current_girder->surface_y_at(position.x);
                }
            }
            break;
        case State::Climbing:
            velocity.x = 0.f;
            velocity.y = climbing_dir;

            if (position.y > current_ladder->get_lower_end()->surface_y_at(position.x)) {
                state = State::OnGirder;
                current_girder = current_ladder->get_lower_end();
                position.y = current_girder->surface_y_at(position.x);
            } else if (position.y < current_ladder->get_upper_end()->surface_y_at(position.x)) {
                state = State::OnGirder;
                current_girder = current_ladder->get_upper_end();
                position.y = current_girder->surface_y_at(position.x);
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
    if (state == State::OnGirder) {
        state = State::InAir;
        velocity.y = -constants::PLAYER_JUMP_SPEED;
    }
}

const sf::RectangleShape& Player::get_shape() const {
    return shape;
}

const Girder *Player::find_girder_below(const std::vector<Girder>& girders) const {
    for (auto it = girders.begin(); it != girders.end(); ++it) {
        const Girder &girder = *it;
        if (girder.covers_x(position.x)) {
            float surface = girder.surface_y_at(position.x);
            if (position.y >= surface && surface >= position.y - constants::PLAYER_HEIGHT / 2.f) {
                return &girder;
            }
        }
    }
    return nullptr;
}

const Ladder *Player::find_ladder_leading_up(const std::vector<Ladder>& ladders) const {
    for (auto it = ladders.begin(); it != ladders.end(); ++it) {
        const Ladder &ladder = *it;
        const float x_pos = ladder.get_x_pos();
        if (ladder.get_lower_end() == current_girder && x_pos - constants::PLAYER_WIDTH / 2.f <= position.x && position.x <= x_pos + constants::PLAYER_WIDTH / 2.f) {
            return &ladder;
        }
    }
    return nullptr;
}

const Ladder *Player::find_ladder_leading_down(const std::vector<Ladder>& ladders) const {
    for (auto it = ladders.begin(); it != ladders.end(); ++it) {
        const Ladder &ladder = *it;
        const float x_pos = ladder.get_x_pos();
        if (ladder.get_upper_end() == current_girder && x_pos - constants::PLAYER_WIDTH / 2.f <= position.x && position.x <= x_pos + constants::PLAYER_WIDTH / 2.f) {
            return &ladder;
        }
    }
    return nullptr;
}
