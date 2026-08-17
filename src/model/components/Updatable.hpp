#ifndef UPDATABLE_HPP
#define UPDATABLE_HPP

#include "../Declarations.hpp"
#include "../util/EntityFromComponentAux.hpp"

/**
 * @brief Behaviour interface for entities that need a per-frame update step.
 *
 * Entities such as the player and barrels implement this interface to integrate
 * their movement and state changes with the game loop.
 */
class Updatable : public EntityFromComponentAux {
public:
    virtual ~Updatable() {}

    /**
     * @brief Advances the entity by one simulation step.
     * @param dt Duration of the simulation step in seconds.
     * @param level Level containing the surrounding entities and platform data.
     */
    virtual void update(float dt, Stage &level) = 0;
};

#endif
