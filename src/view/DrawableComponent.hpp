#ifndef DRAWABLE_COMPONENT_H
#define DRAWABLE_COMPONENT_H

#include "LayerStack.hpp"

class DrawableComponent {
public:
    ~DrawableComponent() {}

    virtual void draw(LayerStack &layer_stack) = 0;
};

#endif
