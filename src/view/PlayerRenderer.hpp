#ifndef PLAYER_RENDERER_HPP
#define PLAYER_RENDERER_HPP

#include "DrawableComponent.hpp"
#include "../model/entities/Player.hpp"
#include "AssetsManager.hpp"

/**
 * @brief Renderer for the player entity.
 */
class PlayerRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the player renderer for a concrete entity.
     * @param player Player instance to render.
     */
    PlayerRenderer(std::shared_ptr<Player> player, AssetsManager &assets_manager) : player(player), player_sprite(assets_manager.get_texture(AssetsManager::TextureId::Jumpman)) {
        sf::FloatRect sprite_bounds = player_sprite.getLocalBounds();
        player_sprite.setOrigin({sprite_bounds.size.x / 2.f, sprite_bounds.size.y});
        // player_sprite.setScale({2.f, 2.f});
    }

    /**
     * @brief Draws the player into the player layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override {
        player_sprite.setPosition(player->get_position());
        player_sprite.setScale({player->is_facing_right() ? 2.f : -2.f, 2.f});
        layer_stack.get_layer(LayerStack::LayerId::Player).add_to_layer(player_sprite); // TODO: add walking/climbing animation
    }

private:
    std::shared_ptr<Player> player;
    sf::Sprite player_sprite;
};

#endif
