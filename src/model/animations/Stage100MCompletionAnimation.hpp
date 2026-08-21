#ifndef STAGE_100M_COMPLETION_ANIMATION_HPP
#define STAGE_100M_COMPLETION_ANIMATION_HPP

#include "AbstractAnimation.hpp"
#include "AnimationVisitor.hpp"

class Stage100MCompletionAnimation : public AbstractAnimation {
public:
    enum class State {
        NotStarted,
        Finished,
    };

    Stage100MCompletionAnimation(Stage &stage)
        : AbstractAnimation(stage) {}

    void update(float dt) override {
        AbstractAnimation::update(dt);
        time_elapsed_in_state += dt;
        
        bool flag = true;
        while(flag) {
            flag = false;
            switch(state) {
                case State::NotStarted:
                    set_state(State::Finished, flag); // TODO: Implement the actual animation logic here
                    break;
                case State::Finished:
                    return;
            }
        }
    }

    bool check_finished() override {
        return state == State::Finished;
    }

    void accept(AnimationVisitor &visitor) override {
        visitor.visit(*this);
    }

    State get_state() const {
        return state;
    }

    float get_time_elapsed_in_state() const {
        return time_elapsed_in_state;
    }

    bool is_exit_animation() const override {
        return true;
    }

private:
    State state = State::NotStarted;
    float time_elapsed_in_state = 0.0f;

    void set_state(State new_state, bool &flag) {
        flag = true;
        state = new_state;
        time_elapsed_in_state = 0.0f;
    }
};

#endif
