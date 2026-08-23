#ifndef BARREL_STACK_RENDERER_HPP
#define BARREL_STACK_RENDERER_HPP

#include <memory>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Angle.hpp>

#include "DK/model/Declarations.hpp"
#include "DK/view/DrawableComponent.hpp"

/**
 * @brief Renderer for the barrel stack entity.
 */
class BarrelStackRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the barrel stack renderer for a concrete entity.
     * @param barrel_stack Barrel stack instance to render.
     * @param assets_manager Assets manager used for retrieving assets.
     */
    BarrelStackRenderer(std::shared_ptr<BarrelStack> barrel_stack, AssetsManager &assets_manager)
        : barrel_stack(barrel_stack), assets_manager(assets_manager) {}

    /**
     * @brief Draws the barrel stack into the object layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override;

private:
    std::shared_ptr<BarrelStack> barrel_stack;
    AssetsManager &assets_manager;

    /**
     * @brief Draws a single barrel of the stack into the object layer.
     *
     * @param layer_stack The layer stack used for rendering.
     * @param left true if the barrel is on the left side of the stack, false otherwise.
     * @param bottom true if the barrel is on the bottom side of the stack, false otherwise.
     */
    void draw_single_barrel(LayerStack &layer_stack, bool left, bool bottom);
};

#endif
