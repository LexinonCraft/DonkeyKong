#include "DK/model/animations/PlayerDeathAnimation.hpp"

#include "DK/Constants.hpp"

void PlayerDeathAnimation::update(float dt) {
    AbstractAnimation::update(dt);
    time_elapsed_in_state += dt;

    bool flag = true;
    while (flag) {
        flag = false;
        switch (state) {
            case State::NotStarted:
                set_state(State::BeforeRotating, flag);
                player->start_animation(this);
                break;
            case State::BeforeRotating:
                if (get_time_elapsed() < constants::PLAYER_DYING_ANIMATION_TIME_BEFORE_ROTATION) {
                    break;
                }
                set_state(State::Rotating, flag);
                break;
            case State::Rotating:
                if (get_time_elapsed_in_state() < constants::PLAYER_DYING_ANIMATION_ROTATION_LENGTH) {
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
