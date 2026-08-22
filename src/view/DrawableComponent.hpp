#ifndef DRAWABLE_COMPONENT_HPP
#define DRAWABLE_COMPONENT_HPP

#include "DK/view/LayerStack.hpp"
#include "DK/model/Stage.hpp"

/**
 * @brief Abstract render adapter for a world entity.
 *
 * A drawable component takes a concrete entity and writes its visual
 * representation to the correct render layer.
 */
class DrawableComponent {
public:
    virtual ~DrawableComponent() = default;

    /**
     * @brief Draws this component into the supplied layer stack.
     * @param layer_stack Stack of render layers used by the current view.
     */
    virtual void draw(LayerStack &layer_stack) = 0;

    virtual void update(float dt, Stage &stage) {}
};

#endif
