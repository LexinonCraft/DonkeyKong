#include "DK/view/renderers/HammerRenderer.hpp"

#include "DK/Constants.hpp"
#include "DK/model/entities/HammerPowerUp.hpp"
#include "DK/util/Positions.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/LayerStack.hpp"

void HammerRenderer::draw(LayerStack &layer_stack) {
    sf::Sprite sprite(assets_manager.get_texture(AssetsManager::TextureId::Hammer));
    set_origin(sprite, AnchorPosition::BottomCenter);
    sprite.setPosition(hammer->get_position());
    set_to_size(sprite, {constants::HAMMER_RENDER_SIZE, constants::HAMMER_RENDER_SIZE});
    layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(sprite);
}
