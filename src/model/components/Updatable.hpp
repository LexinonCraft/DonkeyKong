#ifndef UPDATABLE_HPP
#define UPDATABLE_HPP

#include "DK/model/Declarations.hpp"
#include "DK/model/util/EntityFromComponentAux.hpp"

/**
 * @brief Behaviour interface for entities that need a per-frame update step.
 *
 * Entities such as the player and barrels implement this interface to integrate
 * their movement and state changes with the game loop.
 */
class Updatable : public EntityFromComponentAux {
public:
    ~Updatable() override = default;

    /**
     * @brief Advances the entity by one simulation step.
     * @param dt Duration of the simulation step in seconds.
     * @param stage Stage containing the surrounding entities and platform data.
     */
    virtual void update(float dt, Stage &stage) = 0;
};

#endif
