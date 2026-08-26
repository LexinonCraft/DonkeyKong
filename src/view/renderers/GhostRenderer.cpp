#include "DK/view/renderers/GhostRenderer.hpp"

#include "DK/Constants.hpp"
#include "DK/model/entities/Ghost.hpp"
#include "DK/util/Math.hpp"
#include "DK/util/Positions.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/LayerStack.hpp"

void GhostRenderer::draw(LayerStack &layer_stack) {
    AssetsManager::TextureId texture_id = mod(floor_to_int(animation_timer / constants::GHOST_ANIMATION_INTERVAL), 2)
                                              ? AssetsManager::TextureId::Ghost1
                                              : AssetsManager::TextureId::Ghost2;
    sf::Sprite ghost_sprite(assets_manager.get_texture(texture_id));
    set_origin(ghost_sprite, AnchorPosition::BottomCenter);
    ghost_sprite.setPosition(ghost->get_position() + sf::Vector2f{0.f, -constants::GHOST_LIFT}); // Adjust for ghost lift
    scale(ghost_sprite, constants::GHOST_RENDER_SCALE);
    flip_horizontally(ghost_sprite, !ghost->is_moving_right());
    layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(ghost_sprite);
}

void GhostRenderer::update(float dt, Stage &stage) {
    animation_timer += dt;
    if (animation_timer >= constants::GHOST_ANIMATION_FRAME_COUNT * constants::GHOST_ANIMATION_INTERVAL) {
        animation_timer -= constants::GHOST_ANIMATION_FRAME_COUNT * constants::GHOST_ANIMATION_INTERVAL;
    }
}
