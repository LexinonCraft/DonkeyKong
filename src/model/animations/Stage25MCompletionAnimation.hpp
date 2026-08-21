#ifndef STAGE_25M_COMPLETION_ANIMATION_HPP
#define STAGE_25M_COMPLETION_ANIMATION_HPP

#include <memory>

#include "AbstractAnimation.hpp"
#include "../entities/Player.hpp"
#include "../entities/DonkeyKong.hpp"
#include "../entities/Pauline.hpp"
#include "AnimationVisitor.hpp"

class Stage25MCompletionAnimation : public AbstractAnimation {
public:
    enum class State {
        NotStarted,
        United,
        Climbing,
        Finished,
    };

    Stage25MCompletionAnimation(Stage &stage, std::shared_ptr<Player> player, std::shared_ptr<DonkeyKong> donkey_kong, std::shared_ptr<Pauline> pauline)
        : AbstractAnimation(stage), player(player), donkey_kong(donkey_kong), pauline(pauline) {}

    void update(float dt) override {
        AbstractAnimation::update(dt);
        time_elapsed_in_state += dt;
        
        bool flag = true;
        while(flag) {
            flag = false;
            switch(state) {
                case State::NotStarted:
                    set_state(State::United, flag);
                    player->set_facing_right(false);
                    pauline->start_animation(this);
                    donkey_kong->start_animation(this);
                    break;
                case State::United:
                    if(get_time_elapsed() < 3.0f) {
                        break;
                    }
                    set_state(State::Climbing, flag);
                    donkey_kong->set_position({205.f, -550.f});
                    break;
                case State::Climbing:
                    donkey_kong->set_position(donkey_kong->get_position() - sf::Vector2f(0.f, 75.f * dt));
                    if (get_time_elapsed() < 5.0f) {
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
    std::shared_ptr<DonkeyKong> donkey_kong;
    std::shared_ptr<Pauline> pauline;
    float time_elapsed_in_state = 0.0f;

    void set_state(State new_state, bool &flag) {
        flag = true;
        state = new_state;
        time_elapsed_in_state = 0.0f;
    }
};

#endif
