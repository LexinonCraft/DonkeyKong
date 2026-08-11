#ifndef UPDATABLE_HPP
#define UPDATABLE_HPP

#include "../Declarations.hpp"

class Updatable {
public:
    virtual ~Updatable() {}

    virtual void update(float dt, Level &level) = 0;
};

#endif
