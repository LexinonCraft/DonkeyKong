#ifndef UPDATABLE_H
#define UPDATABLE_H

#include "../Declarations.hpp"

class Updatable {
public:
    virtual ~Updatable() {}

    virtual void update(float dt, Level &level) = 0;
};

#endif
