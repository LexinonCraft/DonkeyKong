#ifndef UPDATABLE_HPP
#define UPDATABLE_HPP

#include "../Declarations.hpp"
#include "../util/EntityFromComponentAux.hpp"

class Updatable : public EntityFromComponentAux {
public:
    virtual ~Updatable() {}

    virtual void update(float dt, Level &level) = 0;
};

#endif
