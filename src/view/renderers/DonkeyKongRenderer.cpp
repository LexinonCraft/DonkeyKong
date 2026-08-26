#include "DK/view/renderers/DonkeyKongRenderer.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include "DK/Constants.hpp"
#include "DK/model/animations/Stage100MCompletionAnimation.hpp"
#include "DK/model/animations/Stage25MCompletionAnimation.hpp"
#include "DK/model/entities/DonkeyKong.hpp"
#include "DK/util/Math.hpp"
#include "DK/util/Positions.hpp"
#include "DK/view/LayerStack.hpp"

void DonkeyKongRenderer::draw(LayerStack &layer_stack) {
    AssetsManager::TextureId texture_id;
    bool flip = false;
    bool render_barrel = false;
    switch (donkey_kong->get_state()) {
        case DonkeyKong::State::Idle:
            texture_id = AssetsManager::TextureId::DonkeyKongStill;
            flip = false;
            break;
        case DonkeyKong::State::ThrowingBarrel:
            switch (mod(floor_to_int(donkey_kong->get_action_timer() / constants::BARREL_THROW_ANIMATION_INTERVAL),
                        constants::DONKEY_KONG_THROW_ANIMATION_FRAME_COUNT)) {
                case 0:
                    texture_id = AssetsManager::TextureId::DonkeyKongThrowingSide;
                    flip = false;
                    break;
                case 1:
                    texture_id = AssetsManager::TextureId::DonkeyKongThrowingFront;
                    flip = false;
                    render_barrel = true;
                    break;
                case 2:
                    texture_id = AssetsManager::TextureId::DonkeyKongThrowingSide;
                    flip = true;
                    break;
                case 3:
                    texture_id = AssetsManager::TextureId::DonkeyKongStill;
                    flip = false;
                    break;
                default:
                    throw std::logic_error("Invalid animation frame for Donkey Kong throwing barrel.");
            }
            break;
        case DonkeyKong::State::Angry:
            texture_id = AssetsManager::TextureId::DonkeyKongAngry1;
            flip = floor_to_int(donkey_kong->get_action_timer() / constants::DONKEY_KONG_ANGRY_ANIMATION_INTERVAL) % 2 == 0;
            break;
        case DonkeyKong::State::Animated:
            {
                DonkeyKongAnimationVisitor visitor;
                donkey_kong->get_current_animation()->accept(visitor);
                texture_id = visitor.texture_id;
                flip = visitor.flip;
            }
            break;
    }

    sf::Sprite donkey_kong_sprite(assets_manager.get_texture(texture_id));
    set_origin(donkey_kong_sprite, AnchorPosition::BottomCenter);
    donkey_kong_sprite.setPosition(donkey_kong->get_position());
    scale(donkey_kong_sprite, constants::DONKEY_KONG_RENDER_SCALE);
    flip_horizontally(donkey_kong_sprite, flip);
    layer_stack.get_layer(LayerStack::LayerId::DonkeyKong).add_to_layer(donkey_kong_sprite);

    if (render_barrel) {
        sf::Sprite barrel_sprite(assets_manager.get_texture(AssetsManager::TextureId::BarrelSide1));
        set_origin(barrel_sprite, AnchorPosition::BottomCenter);
        barrel_sprite.setPosition(
            {donkey_kong->get_position().x, donkey_kong->get_position().y - constants::DONKEY_KONG_HOLDED_BARREL_OFFSET_Y});
        set_to_size(barrel_sprite, {constants::BARREL_RADIUS * constants::BARREL_RENDER_SIZE_FACTOR,
                                    constants::BARREL_RADIUS * constants::BARREL_RENDER_SIZE_FACTOR});
        layer_stack.get_layer(LayerStack::LayerId::DonkeyKong).add_to_layer(barrel_sprite);
    }
}

void DonkeyKongRenderer::DonkeyKongAnimationVisitor::visit(Stage25MCompletionAnimation &animation) {
    flip = false;
    switch (animation.get_state()) {
        case Stage25MCompletionAnimation::State::NotStarted:
        case Stage25MCompletionAnimation::State::United:
            texture_id = AssetsManager::TextureId::DonkeyKongStill;
            break;
        case Stage25MCompletionAnimation::State::Climbing:
        case Stage25MCompletionAnimation::State::Finished:
            texture_id = mod(floor_to_int(animation.get_time_elapsed_in_state() / constants::DONKEY_KONG_CLIMBING_FRAME_INTERVAL), 2) == 0
                             ? AssetsManager::TextureId::DonkeyKongClimbing1
                             : AssetsManager::TextureId::DonkeyKongClimbing2;
            break;
    }
}

void DonkeyKongRenderer::DonkeyKongAnimationVisitor::visit(Stage100MCompletionAnimation &animation) {
    flip = false;
    switch (animation.get_state()) {
        case Stage100MCompletionAnimation::State::NotStarted:
            texture_id = AssetsManager::TextureId::DonkeyKongStill;
            break;
        case Stage100MCompletionAnimation::State::BeforeFall:
            texture_id = AssetsManager::TextureId::DonkeyKongAngry1;
            flip = mod(floor_to_int(animation.get_time_elapsed_in_state() / constants::DONKEY_KONG_BEFORE_FALL_FRAME_INTERVAL), 2) == 0;
            break;
        case Stage100MCompletionAnimation::State::Falling:
            texture_id = AssetsManager::TextureId::DonkeyKongFalling1;
            break;
        case Stage100MCompletionAnimation::State::Impact:
            texture_id = AssetsManager::TextureId::DonkeyKongFalling2;
            break;
        case Stage100MCompletionAnimation::State::United:
        case Stage100MCompletionAnimation::State::Finished:
            switch (mod(floor_to_int(animation.get_time_elapsed_in_state() / constants::DONKEY_KONG_AFTER_FALL_FRAME_INTERVAL),
                        constants::DONKEY_KONG_AFTER_FALL_ANIMATION_FRAME_COUNT)) {
                case 0:
                    texture_id = AssetsManager::TextureId::DonkeyKongFalling1;
                    break;
                case 1:
                    texture_id = AssetsManager::TextureId::DonkeyKongFalling2;
                    break;
                case 2:
                    texture_id = AssetsManager::TextureId::DonkeyKongFalling3;
                    break;
            }
            break;
    }
}
