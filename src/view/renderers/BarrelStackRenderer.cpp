#include "DK/view/renderers/BarrelStackRenderer.hpp"

#include "DK/Constants.hpp"

void BarrelStackRenderer::draw(LayerStack &layer_stack) {
    draw_single_barrel(layer_stack, false, false);
    draw_single_barrel(layer_stack, false, true);
    draw_single_barrel(layer_stack, true, false);
    draw_single_barrel(layer_stack, true, true);
}

void BarrelStackRenderer::draw_single_barrel(LayerStack &layer_stack, bool left, bool bottom) {
    sf::Sprite sprite(assets_manager.get_texture(AssetsManager::TextureId::BarrelSide1));
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setScale({constants::BARREL_RADIUS * 2.5f / bounds.size.x, constants::BARREL_RADIUS * 2.5f / bounds.size.y});
    sprite.setOrigin({bounds.size.x, bounds.size.y / 2.f});
    sprite.setRotation(sf::degrees(90));
    auto position = barrel_stack->get_position();
    sprite.setPosition({position.x + (left ? -1.f : 1.f) * constants::BARREL_RADIUS * 2.5f * 5.f / 16.f,
                        position.y + (bottom ? 0.f : -1.f) * constants::BARREL_RADIUS * 2.5f});
    layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(sprite);
}
