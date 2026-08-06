#include "PlayerControl.hpp"

PlayerControl::PlayerControl(Layer &layer) :
    layer(layer),
    player(std::make_unique<Player>())
{}

Player &PlayerControl::get_player() const {
    return *player;
}

void PlayerControl::set_horizontal_direction(Player::HorizontalDirection dir) {
    player->set_horizontal_direction(dir);
}

void PlayerControl::set_vertical_direction(Player::VerticalDirection dir) {
    player->set_vertical_direction(dir);
}

void PlayerControl::jump() {
    player->jump();
}

void PlayerControl::update(Level &level, float dt) {
    player->update(level, dt);
}

void PlayerControl::draw() {
    layer.add_to_layer(player->get_shape());
}
