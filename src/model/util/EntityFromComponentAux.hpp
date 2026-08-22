#ifndef ENTITY_FROM_COMPONENT_AUX_HPP
#define ENTITY_FROM_COMPONENT_AUX_HPP

#include "DK/model/util/BaseEntity.hpp"

/**
 * @brief Common interface for component-side adapters that need access to their entity.
 *
 * This is used by behaviour interfaces such as Platform, Updatable and Climbable
 * so that a component can request the concrete entity it belongs to.
 */
class EntityFromComponentAux {
public:
    virtual ~EntityFromComponentAux() {}

    /**
     * @brief Returns the entity associated with the component adapter.
     * @return Reference to the owning entity.
     */
    virtual BaseEntity &get_entity() = 0;
};

#endif
