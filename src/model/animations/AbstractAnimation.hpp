#ifndef ABSTRACT_ANIMATION_HPP
#define ABSTRACT_ANIMATION_HPP

#include "DK/model/Declarations.hpp"

/**
 * @brief Abstract base class for synchronized animations interrupting the game logic.
 */
class AbstractAnimation {
public:
    /**
     * @brief Initializes the animation.
     * @param stage The stage where the animation is played.
     */
    AbstractAnimation(Stage &stage) : stage(stage) {}

    virtual ~AbstractAnimation() = default;

    /**
     * @brief Updates the animation state.
     * @param dt Time elapsed since the last update.
     */
    virtual void update(float dt) { time_elapsed += dt; }

    /** @returns The stage where the animation is played. */
    Stage &get_stage() const { return stage; }

    /** @returns Whether the animation is finished. */
    virtual bool is_finished() = 0;

    /** @brief Accepts a visitor for the animation. */
    virtual void accept(class AnimationVisitor &visitor) = 0;

    /** @returns Whether the scene should change after finishing the animation. */
    virtual bool is_exit_animation() const { return false; }

protected:
    /** @returns The total time elapsed since the animation started. */
    float get_time_elapsed() const { return time_elapsed; }

private:
    float time_elapsed = 0.0f;
    Stage &stage;
};

#endif
