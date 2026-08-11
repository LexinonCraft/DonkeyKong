#ifndef PLAYER_RENDERER_HPP
#define PLAYER_RENDERER_HPP

#include "DrawableComponent.hpp"
#include "../model/entities/Player.hpp"

class PlayerRenderer : public DrawableComponent {
public:
    PlayerRenderer(std::shared_ptr<Player> player) : player(player) {}

    void draw(LayerStack &layer_stack) override {
        layer_stack.get_layer(LayerStack::LayerId::Player).add_to_layer(player->get_shape()); // TODO
    }

private:
    std::shared_ptr<Player> player;
};

#endif
