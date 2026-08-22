#include "DK/view/renderers/GhostRenderer.hpp"

#include "DK/Constants.hpp"
#include "DK/util/Math.hpp"

void GhostRenderer::draw(LayerStack &layer_stack) {
    AssetsManager::TextureId texture_id = mod(floor_to_int(animation_timer / constants::GHOST_ANIMATION_INTERVAL), 2)
                                              ? AssetsManager::TextureId::Ghost1
                                              : AssetsManager::TextureId::Ghost2;
    sf::Sprite ghost_sprite(assets_manager.get_texture(texture_id));
    sf::FloatRect ghost_bounds = ghost_sprite.getLocalBounds();
    ghost_sprite.setOrigin({ghost_bounds.size.x / 2.f, ghost_bounds.size.y});
    ghost_sprite.setPosition(ghost->get_position() + sf::Vector2f{0.f, -constants::GHOST_LIFT}); // Adjust for ghost lift
    ghost_sprite.setScale({ghost->is_moving_right() ? 2.f : -2.f, 2.f});
    layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(ghost_sprite);
}

void GhostRenderer::update(float dt, Stage &stage) {
    animation_timer += dt;
    if (animation_timer >= 2 * constants::GHOST_ANIMATION_INTERVAL) {
        animation_timer -= 2 * constants::GHOST_ANIMATION_INTERVAL;
    }
}
