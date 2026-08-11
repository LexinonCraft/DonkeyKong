#ifndef BARREL_RENDERER_HPP
#define BARREL_RENDERER_HPP

#include "DrawableComponent.hpp"
#include "../model/entities/Barrel.hpp"

class BarrelRenderer : public DrawableComponent {
public:
    BarrelRenderer(std::weak_ptr<Barrel> barrel) : barrel(barrel) {}

    void draw(LayerStack &layer_stack) override {
        auto barrel_locked = barrel.lock();
        if (!barrel_locked)
            return;

        layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(barrel_locked->get_shape()); // TODO
    }

private:
    std::weak_ptr<Barrel> barrel;
};

#endif
