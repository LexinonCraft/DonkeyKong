#ifndef GIRDER_RENDERER_HPP
#define GIRDER_RENDERER_HPP

#include "DrawableComponent.hpp"
#include "../model/entities/Girder.hpp"

class GirderRenderer : public DrawableComponent {
public:
    GirderRenderer(std::weak_ptr<Girder> girder) : girder(girder) {}

    void draw(LayerStack &layer_stack) override {
        auto girder_locked = girder.lock();
        if (!girder_locked)
            return;

        layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(girder_locked->get_shape()); // TODO
    }

private:
    std::weak_ptr<Girder> girder;
};

#endif
