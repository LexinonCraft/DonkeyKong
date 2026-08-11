#ifndef PLAYER_RENDERER_HPP
#define PLAYER_RENDERER_HPP

#include "DrawableComponent.hpp"
#include "../model/entities/Player.hpp"

class PlayerRenderer : public DrawableComponent {
public:
    PlayerRenderer(std::weak_ptr<Player> player) : player(player) {}

    void draw(LayerStack &layer_stack) override {
        auto player_locked = player.lock();
        if (!player_locked)
            return;

        layer_stack.get_layer(LayerStack::LayerId::Player).add_to_layer(player_locked->get_shape()); // TODO
    }

private:
    std::weak_ptr<Player> player;
};

#endif
