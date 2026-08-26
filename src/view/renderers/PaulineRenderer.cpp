#include "DK/view/renderers/PaulineRenderer.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Angle.hpp>

#include "DK/Constants.hpp"
#include "DK/model/Stage.hpp"
#include "DK/model/animations/Stage100MCompletionAnimation.hpp"
#include "DK/model/animations/Stage25MCompletionAnimation.hpp"
#include "DK/model/entities/Pauline.hpp"
#include "DK/util/Math.hpp"
#include "DK/util/Positions.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/LayerStack.hpp"

void PaulineRenderer::draw(LayerStack &layer_stack) {
    auto position = pauline->get_position();

    AssetsManager::TextureId texture_id;
    bool help = false;
    bool draw_pauline = true;
    bool draw_heart = false;
    bool heart_broken = false;
    switch (pauline->get_state()) {
        case Pauline::State::Normal:
            if (animation_timer < constants::PAULINE_SCREAM_ANIMATION_INTERVAL * constants::PAULINE_SCREAM_ANIMATION_FRAMES &&
                !suppress_scream) {
                switch (mod(floor_to_int(animation_timer / constants::PAULINE_SCREAM_ANIMATION_INTERVAL), 2)) {
                    case 0:
                        texture_id = AssetsManager::TextureId::PaulineScream1;
                        break;
                    case 1:
                        texture_id = AssetsManager::TextureId::PaulineScream2;
                        break;
                    default:
                        throw std::logic_error("Invalid animation frame for Pauline's scream animation.");
                }
                help = true;
            } else {
                texture_id = AssetsManager::TextureId::PaulineStill;
                help = false;
            }
            draw_pauline = true;
            draw_heart = false;
            break;
        case Pauline::State::Animated:
            {
                PaulineAnimationVisitor visitor;
                pauline->get_current_animation()->accept(visitor);
                draw_pauline = visitor.draw_pauline;
                draw_heart = visitor.draw_heart;
                heart_broken = visitor.heart_broken;
            }
            texture_id = AssetsManager::TextureId::PaulineStill;
            break;
        default:
            throw std::logic_error("Invalid state for PaulineRenderer.");
    }

    if (draw_pauline) {
        sf::Sprite pauline_sprite(assets_manager.get_texture(texture_id));
        sf::FloatRect bounds = pauline_sprite.getLocalBounds();
        set_origin(pauline_sprite, AnchorPosition::BottomCenter);
        auto position = pauline->get_position();
        pauline_sprite.setPosition({position.x, position.y + bounds.size.y * constants::PAULINE_FALL_VERTICAL_OFFSET_FACTOR});
        scale(pauline_sprite, constants::PAULINE_RENDER_SCALE);
        layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(pauline_sprite);
    }

    if (help) {
        sf::Sprite help_sprite(assets_manager.get_texture(AssetsManager::TextureId::Help));
        set_origin(help_sprite, AnchorPosition::BottomCenter);
        help_sprite.setPosition({position.x + constants::PAULINE_HELP_OFFSET, position.y - constants::PAULINE_HELP_OFFSET});
        scale(help_sprite, constants::PAULINE_RENDER_SCALE);
        layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(help_sprite);
    }

    if (draw_heart) {
        sf::Sprite heart_sprite(
            assets_manager.get_texture(!heart_broken ? AssetsManager::TextureId::HeartNormal : AssetsManager::TextureId::HeartBroken));
        set_origin(heart_sprite, AnchorPosition::BottomCenter);
        heart_sprite.setPosition({constants::VIEW_WIDTH / 2.f, position.y - constants::PAULINE_HEART_OFFSET_Y});
        scale(heart_sprite, constants::PAULINE_RENDER_SCALE);
        layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(heart_sprite);
    }
}

void PaulineRenderer::update(float dt, Stage &stage) {
    animation_timer += dt;
    if (animation_timer > constants::PAULINE_ANIMATION_LENGTH) {
        animation_timer -= constants::PAULINE_ANIMATION_LENGTH;
    }

    suppress_scream = !stage.is_running();
}

void PaulineRenderer::PaulineAnimationVisitor::visit(Stage25MCompletionAnimation &animation) {
    switch (animation.get_state()) {
        case Stage25MCompletionAnimation::State::NotStarted:
            break;
        case Stage25MCompletionAnimation::State::United:
            draw_heart = true;
            break;
        case Stage25MCompletionAnimation::State::Climbing:
        case Stage25MCompletionAnimation::State::Finished:
            draw_pauline = false;
            draw_heart = true;
            heart_broken = true;
            break;
        default:
            throw std::logic_error("Invalid state for Stage25MCompletionAnimation.");
    }
}

void PaulineRenderer::PaulineAnimationVisitor::visit(Stage100MCompletionAnimation &animation) {
    switch (animation.get_state()) {
        case Stage100MCompletionAnimation::State::NotStarted:
        case Stage100MCompletionAnimation::State::BeforeFall:
        case Stage100MCompletionAnimation::State::Falling:
        case Stage100MCompletionAnimation::State::Impact:
            draw_pauline = false;
            break;
        case Stage100MCompletionAnimation::State::United:
        case Stage100MCompletionAnimation::State::Finished:
            draw_heart = true;
            break;
        default:
            throw std::logic_error("Invalid state for Stage100MCompletionAnimation.");
    }
}
