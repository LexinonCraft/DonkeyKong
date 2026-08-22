#include "DK/view/renderers/HammerRenderer.hpp"

#include "DK/util/Positions.hpp"

void HammerRenderer::draw(LayerStack &layer_stack) {
    sf::Sprite sprite(assets_manager.get_texture(AssetsManager::TextureId::Hammer));
    set_origin(sprite, AnchorPosition::BottomCenter);
    sprite.setPosition(hammer->get_position());
    set_to_size(sprite, {32.f, 32.f});
    layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(sprite);
}
