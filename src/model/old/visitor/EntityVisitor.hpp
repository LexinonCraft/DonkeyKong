#ifndef ENTITY_VISITOR_H
#define ENTITY_VISITOR_H

#include "../Declarations.hpp"

class EntityVisitor {
public:
    virtual ~EntityVisitor() {}

    virtual void visit(const Barrel &barrel) = 0;
    virtual void visit(const Player &player) = 0;

protected:
    EntityVisitor() = default;
};

#endif