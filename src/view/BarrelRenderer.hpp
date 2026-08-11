#ifndef BARREL_RENDERER_HPP
#define BARREL_RENDERER_HPP

#include "DrawableComponent.hpp"
#include "../model/entities/Barrel.hpp"

class BarrelRenderer : public DrawableComponent {
public:
    BarrelRenderer(std::shared_ptr<Barrel> barrel) : barrel(barrel) {}

    void draw(LayerStack &layer_stack) override {
        layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(barrel->get_shape()); // TODO
    }

private:
    std::shared_ptr<Barrel> barrel;
};

#endif
