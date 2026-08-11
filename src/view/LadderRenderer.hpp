#ifndef LADDER_RENDERER_HPP
#define LADDER_RENDERER_HPP

#include "DrawableComponent.hpp"
#include "../model/entities/Ladder.hpp"

class LadderRenderer : public DrawableComponent {
public:
    LadderRenderer(std::weak_ptr<Ladder> ladder) : ladder(ladder) {}

    void draw(LayerStack &layer_stack) override {
        auto ladder_locked = ladder.lock();
        if (!ladder_locked)
            return;

        layer_stack.get_layer(LayerStack::LayerId::Ladders).add_to_layer(ladder_locked->get_shape()); // TODO
    }

private:
    std::weak_ptr<Ladder> ladder;
};

#endif
