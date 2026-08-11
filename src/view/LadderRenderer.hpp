#ifndef LADDER_RENDERER_HPP
#define LADDER_RENDERER_HPP

#include "DrawableComponent.hpp"
#include "../model/entities/Ladder.hpp"

class LadderRenderer : public DrawableComponent {
public:
    LadderRenderer(std::shared_ptr<Ladder> ladder) : ladder(ladder) {}

    void draw(LayerStack &layer_stack) override {
        layer_stack.get_layer(LayerStack::LayerId::Ladders).add_to_layer(ladder->get_shape()); // TODO
    }

private:
    std::shared_ptr<Ladder> ladder;
};

#endif
