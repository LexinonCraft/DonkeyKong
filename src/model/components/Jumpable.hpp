#ifndef JUMPABLE_HPP
#define JUMPABLE_HPP

#include "DK/model/util/EntityFromComponentAux.hpp"

class Jumpable : public EntityFromComponentAux {
public:
    virtual ~Jumpable() {}

    virtual void check_jumps_over(const Player &player, Stage &stage) = 0;
};

#endif
