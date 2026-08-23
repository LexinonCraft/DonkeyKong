#include "DK/model/animations/Stage25MCompletionAnimation.hpp"

#include "DK/model/entities/DonkeyKong.hpp"
#include "DK/model/entities/Pauline.hpp"
#include "DK/model/entities/Player.hpp"

void Stage25MCompletionAnimation::update(float dt) {
    AbstractAnimation::update(dt);
    time_elapsed_in_state += dt;

    bool flag = true;
    while (flag) {
        flag = false;
        switch (state) {
            case State::NotStarted:
                set_state(State::United, flag);
                player->set_facing_right(false);
                pauline->start_animation(this);
                donkey_kong->start_animation(this);
                break;
            case State::United:
                if (get_time_elapsed() < 3.0f) {
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
