#ifndef GHOST_RENDERER_HPP
#define GHOST_RENDERER_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "DK/Constants.hpp"
#include "DK/model/entities/Ghost.hpp"
#include "DK/util/Math.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/DrawableComponent.hpp"
#include "DK/view/LayerStack.hpp"

/**
 * @brief Renderer for the ghost entity.
 */
class GhostRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the ghost renderer for a concrete entity.
     * @param ghost Ghost instance to render.
     * @param assets_manager Assets manager used for retrieving assets.
     */
    GhostRenderer(std::shared_ptr<Ghost> ghost, AssetsManager &assets_manager) : ghost(ghost), assets_manager(assets_manager) {}

    /**
     * @brief Draws the ghost into the object layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override {
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

    /**
     * @brief Update the ghost animation timer.
     * 
     * @param dt Time delta since last update.
     * @param stage unused
     */
    void update(float dt, Stage &stage) override {
        animation_timer += dt;
        if (animation_timer >= 2 * constants::GHOST_ANIMATION_INTERVAL) {
            animation_timer -= 2 * constants::GHOST_ANIMATION_INTERVAL;
        }
    }

private:
    std::shared_ptr<Ghost> ghost;
    AssetsManager &assets_manager;
    float animation_timer = 0.f;
};

#endif
