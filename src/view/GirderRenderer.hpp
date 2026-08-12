#ifndef GIRDER_RENDERER_HPP
#define GIRDER_RENDERER_HPP

#include "DrawableComponent.hpp"
#include "../model/entities/Girder.hpp"

/**
 * @brief Renderer for the girder entity.
 */
class GirderRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the girder renderer for a concrete entity.
     * @param girder Girder instance to render.
     */
    GirderRenderer(std::shared_ptr<Girder> girder) : girder(girder) {}

    /**
     * @brief Draws the girder into the platform layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override {
        layer_stack.get_layer(LayerStack::LayerId::Platforms).add_to_layer(girder->get_shape()); // TODO
    }

private:
    std::shared_ptr<Girder> girder;
};

#endif
