#ifndef PLAYER_RENDERER_HPP
#define PLAYER_RENDERER_HPP

#include "DrawableComponent.hpp"
#include "../model/entities/Player.hpp"
#include "AssetsManager.hpp"
#include "../Constants.hpp"
#include "../util/Math.hpp"

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
        AssetsManager::TextureId texture_id;
        bool flip_sprite = false;
        bool rotate_sprite = false;
        switch (player->get_state()) {
            case Player::State::OnPlatform: {
                float walking_time = player->get_walking_time();
                if (walking_time > 0.0f) {
                    texture_id = static_cast<int>(walking_time / constants::PLAYER_WALKING_ANIMATION_INTERVAL) % 2 == 0 ? AssetsManager::TextureId::JumpmanWalking1 : AssetsManager::TextureId::JumpmanWalking2;
                } else {
                    texture_id = AssetsManager::TextureId::JumpmanStill;
                }
                flip_sprite = !player->is_facing_right();
                break;
            }
            case Player::State::InAir:
                texture_id = player->has_jumped() ? AssetsManager::TextureId::JumpmanJumping : AssetsManager::TextureId::JumpmanStill;
                flip_sprite = !player->is_facing_right();
                break;
            case Player::State::Climbing:
                texture_id = AssetsManager::TextureId::JumpmanClimbing;
                flip_sprite = static_cast<int>(player->get_climbing_time() / constants::PLAYER_CLIMBING_ANIMATION_INTERVAL) % 2 == 0;
                break;
            case Player::State::Dying:
                if (dying_time < constants::PLAYER_DYING_ANIMATION_TIME_BEFORE_ROTATION) {
                    texture_id = AssetsManager::TextureId::JumpmanDying1;
                } else if (dying_time < constants::PLAYER_DYING_ANIMATION_TIME_BEFORE_ROTATION + constants::PLAYER_DYING_ANIMATION_ROTATION_LENGTH) {
                    switch(mod(floor_to_int(dying_time / constants::PLAYER_DYING_ANIMATION_INTERVAL), 4)) {
                        case 0:
                            texture_id = AssetsManager::TextureId::JumpmanDying1;
                            break;
                        case 1:
                            texture_id = AssetsManager::TextureId::JumpmanDying2;
                            break;
                        case 2:
                            texture_id = AssetsManager::TextureId::JumpmanDying1;
                            rotate_sprite = true;
                            break;
                        case 3:
                            texture_id = AssetsManager::TextureId::JumpmanDying2;
                            rotate_sprite = true;
                            break;
                    } 
                } else {
                    texture_id = AssetsManager::TextureId::JumpmanDead;
                }
                break;
        }

        sf::Sprite player_sprite(assets_manager.get_texture(texture_id));
        sf::FloatRect sprite_bounds = player_sprite.getLocalBounds();
        player_sprite.setOrigin({sprite_bounds.size.x / 2.f, rotate_sprite ? 0.f : sprite_bounds.size.y});
        player_sprite.setPosition(player->get_position());
        player_sprite.setScale({flip_sprite ? -2.f : 2.f, 2.f});
        player_sprite.setRotation(sf::degrees(rotate_sprite ? 180.f : 0.f));
        layer_stack.get_layer(LayerStack::LayerId::Player).add_to_layer(player_sprite);
    }

    void update(float dt) override {
        if (player->get_state() == Player::State::Dying) {
            dying_time += dt;
        }
    }

private:
    std::shared_ptr<Player> player;
    AssetsManager &assets_manager;
    float dying_time = 0.0f;
};

#endif
