#ifndef PLAYER_RENDERER_HPP
#define PLAYER_RENDERER_HPP

#include "DrawableComponent.hpp"
#include "../model/entities/Player.hpp"
#include "AssetsManager.hpp"
#include "../Constants.hpp"

/**
 * @brief Renderer for the player entity.
 */
class PlayerRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the player renderer for a concrete entity.
     * @param player Player instance to render.
     */
    PlayerRenderer(std::shared_ptr<Player> player, AssetsManager &assets_manager) : player(player), player_sprite(assets_manager.get_texture(AssetsManager::TextureId::JumpmanStill)), assets_manager(assets_manager) {
        sf::FloatRect sprite_bounds = player_sprite.getLocalBounds();
        player_sprite.setOrigin({sprite_bounds.size.x / 2.f, sprite_bounds.size.y});
        // player_sprite.setScale({2.f, 2.f});
    }

    /**
     * @brief Draws the player into the player layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override {
        AssetsManager::TextureId texture_id;
        float walking_time = player->get_walking_time();
        if (player->has_jumped()) {
            texture_id = AssetsManager::TextureId::JumpmanJumping;
        } else if (walking_time > 0.0f) {
            texture_id = static_cast<int>(walking_time / constants::PLAYER_WALKING_ANIMATION_INTERVAL) % 2 == 0 ? AssetsManager::TextureId::JumpmanWalking1 : AssetsManager::TextureId::JumpmanWalking2;
        } else {
            texture_id = AssetsManager::TextureId::JumpmanStill;
        }
        player_sprite.setTexture(assets_manager.get_texture(texture_id));

        player_sprite.setPosition(player->get_position());
        player_sprite.setScale({player->is_facing_right() ? 2.f : -2.f, 2.f});
        layer_stack.get_layer(LayerStack::LayerId::Player).add_to_layer(player_sprite); // TODO: add walking/climbing animation
    }

private:
    std::shared_ptr<Player> player;
    sf::Sprite player_sprite;
    AssetsManager &assets_manager;
};

#endif
