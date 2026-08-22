#include "DK/view/renderers/PlayerRenderer.hpp"

#include "DK/Constants.hpp"
#include "DK/util/Math.hpp"
#include "DK/util/Positions.hpp"

void PlayerRenderer::draw(LayerStack &layer_stack) {
    bool flip_sprite = false;
    bool rotate_sprite = false;
    bool hammer_origin = false;
    bool render_player = true;
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
            {
                PlayerAnimationVisitor visitor;
                player->get_current_animation()->accept(visitor);
                texture_id = visitor.texture_id;
                flip_sprite = visitor.flip_sprite;
                rotate_sprite = visitor.rotate_sprite;
                render_player = visitor.render_player;
                break;
            }
    }

    if (!render_player) {
        return;
    }

    sf::Sprite player_sprite(assets_manager.get_texture(texture_id));
    sf::FloatRect sprite_bounds = player_sprite.getLocalBounds();
    player_sprite.setOrigin({sprite_bounds.size.x / (hammer_origin ? 4.f : 2.f), sprite_bounds.size.y});
    player_sprite.setPosition(player->get_position());
    scale(player_sprite, 2.f);
    flip_horizontally(player_sprite, flip_sprite);
    rotate_180_degrees(player_sprite, AnchorPosition::Center, rotate_sprite);
    layer_stack.get_layer(LayerStack::LayerId::Player).add_to_layer(player_sprite);
}

void PlayerRenderer::PlayerAnimationVisitor::visit(PlayerDeathAnimation &animation) {
    switch (animation.get_state()) {
        case PlayerDeathAnimation::State::NotStarted:
        case PlayerDeathAnimation::State::BeforeRotating:
            texture_id = AssetsManager::TextureId::JumpmanDying1;
            rotate_sprite = false;
            break;
        case PlayerDeathAnimation::State::Rotating:
            switch (mod(floor_to_int(animation.get_time_elapsed_in_state() / constants::PLAYER_DYING_ANIMATION_INTERVAL), 4)) {
                case 0:
                    texture_id = AssetsManager::TextureId::JumpmanDying1;
                    rotate_sprite = false;
                    break;
                case 1:
                    texture_id = AssetsManager::TextureId::JumpmanDying2;
                    rotate_sprite = false;
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
            break;
        case PlayerDeathAnimation::State::AfterRotating:
        case PlayerDeathAnimation::State::Finished:
            texture_id = AssetsManager::TextureId::JumpmanDead;
            rotate_sprite = false;
            break;
    }
    flip_sprite = false;
}

void PlayerRenderer::PlayerAnimationVisitor::visit(Stage100MCompletionAnimation &animation) {
    switch (animation.get_state()) {
        case Stage100MCompletionAnimation::State::NotStarted:
        case Stage100MCompletionAnimation::State::BeforeFall:
        case Stage100MCompletionAnimation::State::Falling:
        case Stage100MCompletionAnimation::State::Impact:
            render_player = false;
            break;
        case Stage100MCompletionAnimation::State::United:
        case Stage100MCompletionAnimation::State::Finished:
            texture_id = AssetsManager::TextureId::JumpmanStill;
            flip_sprite = true;
            break;
    }
}
