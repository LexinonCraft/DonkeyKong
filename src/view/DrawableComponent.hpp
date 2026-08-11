#ifndef DRAWABLE_COMPONENT_HPP
#define DRAWABLE_COMPONENT_HPP

#include "LayerStack.hpp"

class DrawableComponent {
public:
    ~DrawableComponent() {}

    virtual void draw(LayerStack &layer_stack) = 0;
};

#endif
