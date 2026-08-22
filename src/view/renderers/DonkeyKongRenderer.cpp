#include "DK/view/renderers/DonkeyKongRenderer.hpp"

#include "DK/Constants.hpp"

void DonkeyKongRenderer::draw(LayerStack &layer_stack) {
    render_barrel = false;
    switch (donkey_kong->get_state()) {
        case DonkeyKong::State::Idle:
            texture_id = AssetsManager::TextureId::DonkeyKongStill;
            flip = false;
            break;
        case DonkeyKong::State::ThrowingBarrel:
            switch (mod(floor_to_int(donkey_kong->get_action_timer() / constants::BARREL_THROW_ANIMATION_INTERVAL), 4)) {
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
            donkey_kong->get_current_animation()->accept(*this);
            break;
    }

    sf::Sprite donkey_kong_sprite(assets_manager.get_texture(texture_id));
    sf::FloatRect donkey_kong_bounds = donkey_kong_sprite.getLocalBounds();
    donkey_kong_sprite.setOrigin({donkey_kong_bounds.size.x / 2.f, donkey_kong_bounds.size.y});
    donkey_kong_sprite.setPosition(donkey_kong->get_position());
    donkey_kong_sprite.setScale({flip ? -2.f : 2.f, 2.f});
    layer_stack.get_layer(LayerStack::LayerId::DonkeyKong).add_to_layer(donkey_kong_sprite);

    if (render_barrel) {
        sf::Sprite barrel_sprite(assets_manager.get_texture(AssetsManager::TextureId::BarrelSide1));
        sf::FloatRect barrel_bounds = barrel_sprite.getLocalBounds();
        barrel_sprite.setOrigin({barrel_bounds.size.x / 2.f, barrel_bounds.size.y});
        barrel_sprite.setPosition(
            {donkey_kong->get_position().x, donkey_kong->get_position().y - constants::DONKEY_KONG_HOLDED_BARREL_OFFSET_Y});
        barrel_sprite.setScale(
            {constants::BARREL_RADIUS * 2.5f / barrel_bounds.size.x, constants::BARREL_RADIUS * 2.5f / barrel_bounds.size.y});
        layer_stack.get_layer(LayerStack::LayerId::DonkeyKong).add_to_layer(barrel_sprite);
    }
}
