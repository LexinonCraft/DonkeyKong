#include "PlayerControl.hpp"

PlayerControl::PlayerControl(Layer &layer) :
    layer(layer),
    player(std::make_unique<Player>())
{}

void PlayerControl::set_horizontal_direction(Player::HorizontalDirection dir) {
    player->set_horizontal_direction(dir);
}

void PlayerControl::jump() {
    player->jump();
}

void PlayerControl::start_climbing_up() {
    player->start_climbing_up();
}

void PlayerControl::start_climbing_down() {
    player->start_climbing_down();
}

void PlayerControl::update(float dt, const std::vector<Girder> &girders, const std::vector<Ladder> &ladders) {
    player->update(dt, girders, ladders);
}

void PlayerControl::draw() {
    layer.add_to_layer(player->get_shape());
}
