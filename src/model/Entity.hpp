#ifndef ENTITY_H
#define ENTITY_H

#include "Declarations.hpp"
#include "../util/RepositoryElement.hpp"
#include "../util/Repository.hpp"

/// An abstract entity in the game world (e. g. a barrel or a power-up).
class Entity : public RepositoryElement<Entity> {
public:
    Entity(Ref<Entity> ref) : RepositoryElement<Entity>(ref) {}

    virtual ~Entity() {}

    virtual void update(Level &level, float dt) = 0;

    virtual void accept(EntityVisitor &visitor) const = 0;
};

#endif
