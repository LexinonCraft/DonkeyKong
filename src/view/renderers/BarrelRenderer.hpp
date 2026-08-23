#ifndef BARREL_RENDERER_HPP
#define BARREL_RENDERER_HPP

#include <memory>

#include <SFML/Graphics/Rect.hpp>

#include "DK/model/Declarations.hpp"
#include "DK/view/Declarations.hpp"
#include "DK/view/DrawableComponent.hpp"

/**
 * @brief Renderer for the barrel entity.
 */
class BarrelRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the barrel renderer for a concrete entity.
     * @param barrel Barrel instance to render.
     * @param assets_manager Assets manager used for retrieving assets.
     */
    BarrelRenderer(std::shared_ptr<Barrel> barrel, AssetsManager &assets_manager) : barrel(barrel), assets_manager(assets_manager) {}

    /**
     * @brief Draws the barrel into the object layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override;

private:
    std::shared_ptr<Barrel> barrel;
    AssetsManager &assets_manager;
};

#endif
