#ifndef JUMPABLE_HPP
#define JUMPABLE_HPP

#include "DK/model/util/EntityFromComponentAux.hpp"

/**
 * @brief Behaviour interface for entities that can react when the player jumps over them.
 */
class Jumpable : public EntityFromComponentAux {
public:
    ~Jumpable() override = default;

    /**
     * @brief Processes the player's current jump relative to this entity.
     *
     * Called once per player update for every jumpable entity to track whether
     * the player has jumped over it and apply the resulting effects.
     *
     * @param player Player whose jump is evaluated.
     * @param stage Stage in which resulting effects are applied.
     */
    virtual void check_jumps_over(const Player &player, Stage &stage) = 0;
};

#endif
