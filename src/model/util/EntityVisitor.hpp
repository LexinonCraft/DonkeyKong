#ifndef ENTITY_VISITOR_HPP
#define ENTITY_VISITOR_HPP

#include "../Declarations.hpp"

/**
 * @brief Visitor interface for dispatching behaviour based on the concrete entity type.
 *
 * This is used when a factory needs to create a renderer or similar object for a
 * specific entity implementation without hardcoding entity subclasses.
 */
class EntityVisitor {
public:
    virtual ~EntityVisitor() {}

    /** @brief Visits a barrel entity. */
    virtual void visit(Barrel &barrel) = 0;
    /** @brief Visits a girder entity. */
    virtual void visit(Girder &girder) = 0;
    /** @brief Visits a player entity. */
    virtual void visit(Player &player) = 0;
    /** @brief Visits a ladder entity. */
    virtual void visit(Ladder &ladder) = 0;
};

#endif
