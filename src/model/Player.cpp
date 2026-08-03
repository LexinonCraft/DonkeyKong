#include "Player.hpp"
#include "Constants.hpp"

Player::Player() :
    state(State::InAir),
    current_girder(nullptr),
    current_ladder(nullptr),
    position(0.f, 0.f),
    velocity(0.f, 0.f),
    horizontal_direction(HorizontalDirection::None),
    shape({constants::PLAYER_WIDTH, constants::PLAYER_HEIGHT}) {
        // origin at the rectangle's centre so `position` is the player's centre
        shape.setOrigin({constants::PLAYER_WIDTH / 2.f, constants::PLAYER_HEIGHT / 2.f});
        shape.setFillColor(sf::Color(200, 100, 100)); // light red, stands out on the girders
        shape.setPosition(position);
}

void Player::update(float dt, const std::vector<Girder>& girders, const std::vector<Ladder>& ladders) {
    // TODO
    switch (horizontal_direction) {
        case HorizontalDirection::Left:
            position.x -= constants::PLAYER_WALKING_SPEED * dt;
            break;
        case HorizontalDirection::Right:
            position.x += constants::PLAYER_WALKING_SPEED * dt;
            break;
        case HorizontalDirection::None:
            break;
    }

    shape.setPosition(position);
}

void Player::set_horizontal_direction(HorizontalDirection dir) {
    horizontal_direction = dir;
}

void Player::jump() {
    if (state == State::OnGirder) {
        state = State::InAir;
        velocity.y = -constants::PLAYER_JUMP_SPEED;
    }
}

void Player::start_climbing_up() {
    // TODO
}

void Player::start_climbing_down() {
    // TODO
}

const sf::RectangleShape& Player::get_shape() const {
    return shape;
}
