#ifndef STAGE_100M_COMPLETION_ANIMATION_HPP
#define STAGE_100M_COMPLETION_ANIMATION_HPP

#include <memory>
#include <vector>

#include "AbstractAnimation.hpp"
#include "AnimationVisitor.hpp"
#include "../entities/Player.hpp"
#include "../entities/DonkeyKong.hpp"
#include "../entities/Pauline.hpp"
#include "../entities/Girder.hpp"
#include "../../Constants.hpp"

class Stage100MCompletionAnimation : public AbstractAnimation {
public:
    enum class State {
        NotStarted,
        BeforeFall,
        Falling,
        Impact,
        United,
        Finished,
    };

    Stage100MCompletionAnimation(Stage &stage, std::vector<std::shared_ptr<Girder>> lower_falling_girders, std::shared_ptr<Girder> upper_falling_girder, std::shared_ptr<Player> player, std::shared_ptr<DonkeyKong> donkey_kong, std::shared_ptr<Pauline> pauline)
        : AbstractAnimation(stage), lower_falling_girders(lower_falling_girders), upper_falling_girder(upper_falling_girder), player(player), donkey_kong(donkey_kong), pauline(pauline) {}

    void update(float dt) override {
        AbstractAnimation::update(dt);
        time_elapsed_in_state += dt;
        
        bool flag = true;
        while(flag) {
            flag = false;
            switch(state) {
                case State::NotStarted:
                    set_state(State::BeforeFall, flag);
                    player->start_animation(this);
                    donkey_kong->start_animation(this);
                    pauline->start_animation(this);
                    for (unsigned int i = 0; i < lower_falling_girders.size(); ++i) {
                        lower_falling_girders[i]->set_left({lower_falling_girders[i]->get_left().x, -constants::GIRDER_THICKNESS * (i + 2)});
                        lower_falling_girders[i]->set_right({lower_falling_girders[i]->get_right().x, -constants::GIRDER_THICKNESS * (i + 2)});
                    }
                    upper_falling_girder->set_left({upper_falling_girder->get_left().x, 100.f});
                    upper_falling_girder->set_right({upper_falling_girder->get_right().x, 100.f}); // workaround for hiding girder: put it below the screen
                    break;
                case State::BeforeFall:
                    if(time_elapsed_in_state < 1.5f) {
                        break;
                    }
                    set_state(State::Falling, flag);
                    break;
                case State::Falling:
                    donkey_kong->set_position(donkey_kong->get_position() + sf::Vector2f(0.f, 200.f * dt));
                    if(donkey_kong->get_position().y < -100.f) {
                        break;
                    }
                    set_state(State::Impact, flag);
                    donkey_kong->set_position({donkey_kong->get_position().x, -100.f});
                    break;
                case State::Impact:
                    if(time_elapsed_in_state < 2.5f) {
                        break;
                    }
                    set_state(State::United, flag);
                    upper_falling_girder->set_left({upper_falling_girder->get_left().x, -430.f});
                    upper_falling_girder->set_right({upper_falling_girder->get_right().x, -430.f});
                    pauline->set_position({200.f, -430.f});
                    player->enter_platform(upper_falling_girder, constants::VIEW_WIDTH - 200.f);
                    player->set_facing_right(false);
                    break;
                case State::United:
                    if(time_elapsed_in_state < 5.0f) {
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
    std::vector<std::shared_ptr<Girder>> lower_falling_girders;
    std::shared_ptr<Girder> upper_falling_girder;
    std::shared_ptr<Player> player;
    std::shared_ptr<DonkeyKong> donkey_kong;
    std::shared_ptr<Pauline> pauline;

    State state = State::NotStarted;
    float time_elapsed_in_state = 0.0f;

    void set_state(State new_state, bool &flag) {
        flag = true;
        state = new_state;
        time_elapsed_in_state = 0.0f;
    }
};

#endif
