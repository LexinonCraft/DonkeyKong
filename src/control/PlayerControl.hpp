#ifndef PLAYER_CONTROL_H
#define PLAYER_CONTROL_H

#include <memory>

#include "../view/Layer.hpp"
#include "../model/Player.hpp"
#include "../model/Level.hpp"

/// Owns the player and advances/draws it. When the player moves, the control updates its position.
class PlayerControl {
public:
    PlayerControl(Layer &layer);

    Player &get_player() const;

    void set_horizontal_direction(Player::HorizontalDirection dir);
    void set_vertical_direction(Player::VerticalDirection dir);
    void jump();

    void update(Level &level, float dt);
    void draw();

private:
    Layer &layer;
    std::unique_ptr<Player> player;
};

#endif