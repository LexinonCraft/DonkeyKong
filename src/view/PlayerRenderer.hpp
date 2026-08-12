#ifndef PLAYER_RENDERER_HPP
#define PLAYER_RENDERER_HPP

#include "DrawableComponent.hpp"
#include "../model/entities/Player.hpp"

/**
 * @brief Renderer for the player entity.
 */
class PlayerRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the player renderer for a concrete entity.
     * @param player Player instance to render.
     */
    PlayerRenderer(std::shared_ptr<Player> player) : player(player) {}

    /**
     * @brief Draws the player into the player layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override {
        layer_stack.get_layer(LayerStack::LayerId::Player).add_to_layer(player->get_shape()); // TODO
    }

private:
    std::shared_ptr<Player> player;
};

#endif
