#ifndef ENTITY_FROM_COMPONENT_AUX_HPP
#define ENTITY_FROM_COMPONENT_AUX_HPP

#include "BaseEntity.hpp"

class EntityFromComponentAux {
public:
    virtual ~EntityFromComponentAux() {}

    virtual BaseEntity &get_entity() = 0;
};

#endif
