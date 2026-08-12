#ifndef BARREL_RENDERER_HPP
#define BARREL_RENDERER_HPP

#include "DrawableComponent.hpp"
#include "../model/entities/Barrel.hpp"

/**
 * @brief Renderer for the barrel entity.
 */
class BarrelRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the barrel renderer for a concrete entity.
     * @param barrel Barrel instance to render.
     */
    BarrelRenderer(std::shared_ptr<Barrel> barrel) : barrel(barrel) {}

    /**
     * @brief Draws the barrel into the object layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override {
        layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(barrel->get_shape()); // TODO
    }

private:
    std::shared_ptr<Barrel> barrel;
};

#endif
