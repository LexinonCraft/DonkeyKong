#ifndef ANIMATION_VISITOR_HPP
#define ANIMATION_VISITOR_HPP

#include "DK/model/Declarations.hpp"

class AnimationVisitor {
public:
    virtual void visit(Stage25MCompletionAnimation &animation) {}
    virtual void visit(Stage100MCompletionAnimation &animation) {}
    virtual void visit(PlayerDeathAnimation &animation) {}
};

#endif
