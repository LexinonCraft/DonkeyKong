#ifndef ENTITY_VISITOR_H
#define ENTITY_VISITOR_H

#include "../Declarations.hpp"

class EntityVisitor {
public:
    virtual ~EntityVisitor() {}

    virtual void visit(Barrel &barrel) = 0;
    virtual void visit(Girder &girder) = 0;
};

#endif
