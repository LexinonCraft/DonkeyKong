#ifndef ABSTRACT_ANIMATION_HPP
#define ABSTRACT_ANIMATION_HPP

#include "../Declarations.hpp"

class AbstractAnimation {
public:
    AbstractAnimation(Stage &stage) : stage(stage) {}

    virtual ~AbstractAnimation() = default;

    virtual void update(float dt) {
        time_elapsed += dt;
    }

    Stage &get_stage() const {
        return stage;
    }

    virtual bool check_finished() = 0;

    virtual void accept(class AnimationVisitor &visitor) = 0;

    virtual bool is_exit_animation() const {
        return false;
    }

protected:
    float get_time_elapsed() const {
        return time_elapsed;
    }

private:
    float time_elapsed = 0.0f;
    Stage &stage;
};

#endif
