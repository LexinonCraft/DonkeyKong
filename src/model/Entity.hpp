#ifndef ENTITY_H
#define ENTITY_H

#include "Declarations.hpp"

/// An abstract entity in the game world (e. g. a barrel or a power-up).
class Entity {
public:
    virtual ~Entity() {}

    virtual void update(Level &level, float dt) = 0;

    virtual void accept(EntityVisitor &visitor) const = 0;
};

#endif
