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
    PlayerRenderer(std::shared_ptr<Player> player, AssetsManager &assets_manager) : player(player), assets_manager(assets_manager) {}

    /**
     * @brief Draws the player into the player layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override {
        sf::Sprite player_sprite(assets_manager.get_texture(AssetsManager::TextureId::JumpmanStill));
        sf::FloatRect sprite_bounds = player_sprite.getLocalBounds();
        player_sprite.setOrigin({sprite_bounds.size.x / 2.f, sprite_bounds.size.y});
        bool flip_sprite = !player->is_facing_right();

        AssetsManager::TextureId texture_id;
        float walking_time = player->get_walking_time();
        float climbing_time = player->get_climbing_time();
        if (player->has_jumped()) {
            texture_id = AssetsManager::TextureId::JumpmanJumping;
        } else if (walking_time > 0.0f) {
            texture_id = static_cast<int>(walking_time / constants::PLAYER_WALKING_ANIMATION_INTERVAL) % 2 == 0 ? AssetsManager::TextureId::JumpmanWalking1 : AssetsManager::TextureId::JumpmanWalking2;
        } else if (climbing_time > 0.0f) {
            texture_id = AssetsManager::TextureId::JumpmanClimbing;
            flip_sprite = static_cast<int>(climbing_time / constants::PLAYER_CLIMBING_ANIMATION_INTERVAL) % 2 == 0;
        } else {
            texture_id = AssetsManager::TextureId::JumpmanStill;
        }
        player_sprite.setTexture(assets_manager.get_texture(texture_id));

        player_sprite.setPosition(player->get_position());
        player_sprite.setScale({flip_sprite ? -2.f : 2.f, 2.f});
        layer_stack.get_layer(LayerStack::LayerId::Player).add_to_layer(player_sprite);

        if (player->has_hammer()) {
            draw_hammer(layer_stack);
        }
    }

private:
    std::shared_ptr<Player> player;
    AssetsManager &assets_manager;

    void draw_hammer(LayerStack &layer_stack) {
        const sf::Vector2f player_position = player->get_position();
        const float direction = player->is_facing_right() ? 1.f : -1.f;
        const float animation_time = constants::HAMMER_DURATION - player->get_hammer_time_remaining();
        const bool hammer_up = static_cast<int>(animation_time / constants::HAMMER_SWING_ANIMATION_INTERVAL) % 2 == 0;

        sf::RectangleShape handle;
        sf::RectangleShape head;

        if (hammer_up) {
            const float hammer_x = player_position.x + direction * 6.f;
            handle.setSize({4.f, 18.f});
            handle.setOrigin({2.f, 18.f});
            handle.setPosition({hammer_x, player_position.y - constants::PLAYER_HEIGHT + 8.f});
            head.setSize({18.f, 8.f});
            head.setOrigin({9.f, 4.f});
            head.setPosition({hammer_x, player_position.y - constants::PLAYER_HEIGHT - 11.f});
        } else {
            handle.setSize({20.f, 4.f});
            handle.setOrigin({10.f, 2.f});
            handle.setPosition({player_position.x + direction * 13.f, player_position.y - 18.f});
            head.setSize({8.f, 18.f});
            head.setOrigin({4.f, 9.f});
            head.setPosition({player_position.x + direction * 24.f, player_position.y - 18.f});
        }

        handle.setFillColor(sf::Color(130, 75, 35));
        head.setFillColor(sf::Color(240, 200, 60));
        layer_stack.get_layer(LayerStack::LayerId::Player).add_to_layer(handle);
        layer_stack.get_layer(LayerStack::LayerId::Player).add_to_layer(head);
    }
};

#endif
