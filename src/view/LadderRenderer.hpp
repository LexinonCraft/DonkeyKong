#ifndef LADDER_RENDERER_HPP
#define LADDER_RENDERER_HPP

#include "DrawableComponent.hpp"
#include "../model/entities/Ladder.hpp"

/**
 * @brief Renderer for the ladder entity.
 */
class LadderRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the ladder renderer for a concrete entity.
     * @param ladder Ladder instance to render.
     */
    LadderRenderer(std::shared_ptr<Ladder> ladder) : ladder(ladder) {}

    /**
     * @brief Draws the ladder into the ladder layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override {
        layer_stack.get_layer(LayerStack::LayerId::Ladders).add_to_layer(ladder->get_shape()); // TODO
    }

private:
    std::shared_ptr<Ladder> ladder;
};

#endif
