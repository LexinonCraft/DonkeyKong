#ifndef PLAYER_CONTROL_H
#define PLAYER_CONTROL_H

#include <memory>
#include <vector>

#include "../view/Layer.hpp"
#include "../model/Player.hpp"

/// Owns the player and advances/draws it. When the player moves, the control updates its position.
class PlayerControl {
public:
    PlayerControl(Layer &layer);

    void set_horizontal_direction(Player::HorizontalDirection dir);
    void jump();
    void start_climbing_up();
    void start_climbing_down();

    void update(float dt, const std::vector<Girder> &girders, const std::vector<Ladder> &ladders);
    void draw();

private:
    Layer &layer;
    std::unique_ptr<Player> player;
};

#endif