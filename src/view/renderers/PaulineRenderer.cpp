#include "DK/view/renderers/PaulineRenderer.hpp"

void PaulineRenderer::draw(LayerStack &layer_stack) {
    auto position = pauline->get_position();

    AssetsManager::TextureId texture_id;
    bool help = false;
    draw_pauline = true;
    draw_heart = false;
    heart_broken = false;
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
            pauline->get_current_animation()->accept(*this);
            texture_id = AssetsManager::TextureId::PaulineStill;
            break;
        default:
            throw std::logic_error("Invalid state for PaulineRenderer.");
    }

    if (draw_pauline) {
        sf::Sprite pauline_sprite(assets_manager.get_texture(texture_id));
        sf::FloatRect bounds = pauline_sprite.getLocalBounds();
        pauline_sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y});
        auto position = pauline->get_position();
        pauline_sprite.setPosition({position.x, position.y + bounds.size.y / 32.f * 5.f});
        pauline_sprite.setScale({2.f, 2.f});
        layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(pauline_sprite);
    }

    if (help) {
        sf::Sprite help_sprite(assets_manager.get_texture(AssetsManager::TextureId::Help));
        sf::FloatRect help_bounds = help_sprite.getLocalBounds();
        help_sprite.setOrigin({help_bounds.size.x / 2.f, help_bounds.size.y});
        help_sprite.setPosition({position.x + 40.f, position.y - 40.f});
        help_sprite.setScale({2.f, 2.f});
        layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(help_sprite);
    }

    if (draw_heart) {
        sf::Sprite heart_sprite(
            assets_manager.get_texture(!heart_broken ? AssetsManager::TextureId::HeartNormal : AssetsManager::TextureId::HeartBroken));
        sf::FloatRect heart_bounds = heart_sprite.getLocalBounds();
        heart_sprite.setOrigin({heart_bounds.size.x / 2.f, heart_bounds.size.y});
        heart_sprite.setPosition({constants::VIEW_WIDTH / 2.f, position.y - 40.f});
        heart_sprite.setScale({2.f, 2.f});
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
