#ifndef DRAWABLE_COMPONENT_HPP
#define DRAWABLE_COMPONENT_HPP

#include "DK/model/Declarations.hpp"
#include "DK/view/Declarations.hpp"

/**
 * @brief Component for drawable entities. To be extended by a class specialized to a specific entity type.
 */
class DrawableComponent {
public:
    virtual ~DrawableComponent() = default;

    /**
     * @brief Draws this component into the supplied layer stack.
     * @param layer_stack Stack of render layers used by the current view.
     */
    virtual void draw(LayerStack &layer_stack) = 0;

    /**
     * @brief Updates this component.
     * @param dt Time elapsed since the last update.
     * @param stage The current stage of the game.
     */
    virtual void update(float dt, Stage &stage) {}
};

#endif
