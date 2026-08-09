#ifndef PLATFORM_VISITOR_H
#define PLATFORM_VISITOR_H

#include "../Declarations.hpp"

class PlatformVisitor {
public:
    virtual ~PlatformVisitor() {}

    virtual void visit(const Girder &girder) = 0;

protected:
    PlatformVisitor() = default;
};

#endif