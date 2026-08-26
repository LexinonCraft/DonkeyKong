#include "DK/model/animations/Stage25MCompletionAnimation.hpp"

#include "DK/Constants.hpp"
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
                if (get_time_elapsed() < constants::STAGE_25M_UNITED_DURATION) {
                    break;
                }
                set_state(State::Climbing, flag);
                donkey_kong->set_position({constants::STAGE_25M_COMPLETION_DONKEY_KONG_X, constants::STAGE_25M_COMPLETION_DONKEY_KONG_Y});
                break;
            case State::Climbing:
                donkey_kong->set_position(donkey_kong->get_position() -
                                          sf::Vector2f(0.f, constants::STAGE_25M_COMPLETION_CLIMBING_SPEED * dt));
                if (get_time_elapsed() < constants::STAGE_25M_COMPLETION_DURATION) {
                    break;
                }
                set_state(State::Finished, flag);
                break;
            case State::Finished:
                return;
        }
    }
}
