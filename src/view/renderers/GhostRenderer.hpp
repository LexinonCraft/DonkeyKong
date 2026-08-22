#ifndef GHOST_RENDERER_HPP
#define GHOST_RENDERER_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "DK/model/entities/Ghost.hpp"
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
    void draw(LayerStack &layer_stack) override;

    /**
     * @brief Update the ghost animation timer.
     *
     * @param dt Time delta since last update.
     * @param stage unused
     */
    void update(float dt, Stage &stage) override;

private:
    std::shared_ptr<Ghost> ghost;
    AssetsManager &assets_manager;
    float animation_timer = 0.f;
};

#endif
