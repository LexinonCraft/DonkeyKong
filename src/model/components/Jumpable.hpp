#ifndef JUMPABLE_HPP
#define JUMPABLE_HPP

#include "DK/model/util/EntityFromComponentAux.hpp"

/**
 * @brief Behaviour interface for entities that can react when the player jumps over them.
 */
class Jumpable : public EntityFromComponentAux {
public:
    ~Jumpable() override = default;

    virtual void check_jumps_over(const Player &player, Stage &stage) = 0;
};

#endif
