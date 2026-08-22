#include "DK/view/renderers/PlayerRenderer.hpp"

void PlayerRenderer::draw(LayerStack &layer_stack) {
    flip_sprite = false;
    rotate_sprite = false;
    hammer_origin = false;
    render_player = true;
    switch (player->get_state()) {
        case Player::State::OnPlatform:
            {
                float walking_time = player->get_walking_time();
                if (player->has_hammer()) {
                    const float swing_time = constants::HAMMER_DURATION - player->get_hammer_time_remaining();
                    const bool hammer_up = static_cast<int>(swing_time / constants::HAMMER_SWING_ANIMATION_INTERVAL) % 2 == 0;
                    if (walking_time > 0.0f) {
                        const bool first_stride = static_cast<int>(walking_time / constants::PLAYER_WALKING_ANIMATION_INTERVAL) % 2 == 0;
                        texture_id = hammer_up ? (first_stride ? AssetsManager::TextureId::JumpmanHammerUpWalking1
                                                               : AssetsManager::TextureId::JumpmanHammerUpWalking2)
                                               : (first_stride ? AssetsManager::TextureId::JumpmanHammerDownWalking1
                                                               : AssetsManager::TextureId::JumpmanHammerDownWalking2);
                    } else {
                        texture_id =
                            hammer_up ? AssetsManager::TextureId::JumpmanHammerUpStill : AssetsManager::TextureId::JumpmanHammerDownStill;
                    }
                    hammer_origin = true;
                } else if (walking_time > 0.0f) {
                    texture_id = static_cast<int>(walking_time / constants::PLAYER_WALKING_ANIMATION_INTERVAL) % 2 == 0
                                     ? AssetsManager::TextureId::JumpmanWalking1
                                     : AssetsManager::TextureId::JumpmanWalking2;
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
        case Player::State::Animated:
            player->get_current_animation()->accept(*this);
            break;
    }

    if (!render_player) {
        return;
    }

    sf::Sprite player_sprite(assets_manager.get_texture(texture_id));
    sf::FloatRect sprite_bounds = player_sprite.getLocalBounds();
    player_sprite.setOrigin({sprite_bounds.size.x / (hammer_origin ? 4.f : 2.f), rotate_sprite ? 0.f : sprite_bounds.size.y});
    player_sprite.setPosition(player->get_position());
    player_sprite.setScale({flip_sprite ? -2.f : 2.f, 2.f});
    player_sprite.setRotation(sf::degrees(rotate_sprite ? 180.f : 0.f));
    layer_stack.get_layer(LayerStack::LayerId::Player).add_to_layer(player_sprite);
}
