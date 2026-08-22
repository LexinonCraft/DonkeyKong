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
    virtual void visit(HammerPowerUp &hammer) = 0;
    /** @brief Visits a Donkey Kong entity. */
    virtual void visit(DonkeyKong &donkey_kong) = 0;
    /** @brief Visits a barrel stack entity. */
    virtual void visit(BarrelStack &barrel_stack) = 0;
    /** @brief Visits a Pauline entity. */
    virtual void visit(Pauline &pauline) = 0;
    /** @brief Visits a dissolving platform entity. */
    virtual void visit(DissolvingPlatform &dissolving_platform) = 0;
    /** @brief Visits a ghost entity. */
    virtual void visit(Ghost &ghost) = 0;
    /** @brief Visits a beam entity. */
    virtual void visit(Beam &beam) = 0;
};

#endif
