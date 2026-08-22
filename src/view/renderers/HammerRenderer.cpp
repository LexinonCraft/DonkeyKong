#include "DK/view/renderers/HammerRenderer.hpp"

void HammerRenderer::draw(LayerStack &layer_stack) {
    sf::Sprite sprite(assets_manager.get_texture(AssetsManager::TextureId::Hammer));
    sprite.setOrigin({8.f, 16.f});
    sprite.setPosition(hammer->get_position());
    sprite.setScale({2.f, 2.f});
    layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(sprite);
}
