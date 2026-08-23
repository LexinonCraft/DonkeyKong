#ifndef ANIMATION_VISITOR_HPP
#define ANIMATION_VISITOR_HPP

#include "DK/model/Declarations.hpp"

/**
 * @brief Visitor interface for animations.
 */
class AnimationVisitor {
public:
    /** @brief Visit the completion animation for the 25m stage. */
    virtual void visit(Stage25MCompletionAnimation &animation) {}

    /** @brief Visit the completion animation for the 100m stage. */
    virtual void visit(Stage100MCompletionAnimation &animation) {}

    /** @brief Visit the player death animation. */
    virtual void visit(PlayerDeathAnimation &animation) {}
};

#endif
