#ifndef HAMMER_RENDERER_HPP
#define HAMMER_RENDERER_HPP

#include <memory>

#include <SFML/Graphics/Sprite.hpp>

#include "DK/model/Declarations.hpp"
#include "DK/view/Declarations.hpp"
#include "DK/view/DrawableComponent.hpp"

/**
 * @brief Renderer for the hammer power-up entity.
 */
class HammerRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the hammer renderer for a concrete entity.
     * @param hammer Hammer power-up instance to render.
     * @param assets_manager Assets manager used for retrieving assets.
     */
    HammerRenderer(std::shared_ptr<HammerPowerUp> hammer, AssetsManager &assets_manager) : hammer(hammer), assets_manager(assets_manager) {}

    /**
     * @brief Draws the hammer power-up into the object layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override;

private:
    std::shared_ptr<HammerPowerUp> hammer;
    AssetsManager &assets_manager;
};

#endif
