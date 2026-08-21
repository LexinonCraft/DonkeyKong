#ifndef PLAYER_DEATH_ANIMATION_HPP
#define PLAYER_DEATH_ANIMATION_HPP

#include <memory>

#include "AbstractAnimation.hpp"
#include "../entities/Player.hpp"
#include "../entities/DonkeyKong.hpp"
#include "../entities/Pauline.hpp"
#include "AnimationVisitor.hpp"
#include "../../Constants.hpp"

class PlayerDeathAnimation : public AbstractAnimation {
public:
    enum class State {
        NotStarted,
        BeforeRotating,
        Rotating,
        AfterRotating,
        Finished,
    };

    PlayerDeathAnimation(Stage &stage, std::shared_ptr<Player> player)
        : AbstractAnimation(stage), player(player) {}

    void update(float dt) override {
        AbstractAnimation::update(dt);
        time_elapsed_in_state += dt;
        
        bool flag = true;
        while(flag) {
            flag = false;
            switch(state) {
                case State::NotStarted:
                    set_state(State::BeforeRotating, flag);
                    player->start_animation(this);
                    break;
                case State::BeforeRotating:
                    if(get_time_elapsed() < constants::PLAYER_DYING_ANIMATION_TIME_BEFORE_ROTATION) {
                        break;
                    }
                    set_state(State::Rotating, flag);
                    break;
                case State::Rotating:
                    if(get_time_elapsed_in_state() < constants::PLAYER_DYING_ANIMATION_ROTATION_LENGTH) {
                        break;
                    }
                    set_state(State::AfterRotating, flag);
                    break;
                case State::AfterRotating:
                    if (get_time_elapsed() < constants::PLAYER_DEATH_DURATION) { // TODO
                        break;
                    }
                    set_state(State::Finished, flag);
                    break;
                case State::Finished:
                    return;
            }
        }
    }

    bool is_finished() override {
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
    std::shared_ptr<Player> player;
    float time_elapsed_in_state = 0.0f;

    void set_state(State new_state, bool &flag) {
        flag = true;
        state = new_state;
        time_elapsed_in_state = 0.0f;
    }
};

#endif
