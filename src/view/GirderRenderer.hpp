#ifndef GIRDER_RENDERER_HPP
#define GIRDER_RENDERER_HPP

#include "DrawableComponent.hpp"
#include "../model/entities/Girder.hpp"

class GirderRenderer : public DrawableComponent {
public:
    GirderRenderer(std::shared_ptr<Girder> girder) : girder(girder) {}

    void draw(LayerStack &layer_stack) override {
        layer_stack.get_layer(LayerStack::LayerId::Platforms).add_to_layer(girder->get_shape()); // TODO
    }

private:
    std::shared_ptr<Girder> girder;
};

#endif
