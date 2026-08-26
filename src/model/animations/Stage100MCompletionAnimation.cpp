#include "DK/model/animations/Stage100MCompletionAnimation.hpp"

#include "DK/Constants.hpp"
#include "DK/model/entities/DonkeyKong.hpp"
#include "DK/model/entities/Girder.hpp"
#include "DK/model/entities/Pauline.hpp"
#include "DK/model/entities/Player.hpp"

void Stage100MCompletionAnimation::update(float dt) {
    AbstractAnimation::update(dt);
    time_elapsed_in_state += dt;

    bool flag = true;
    while (flag) {
        flag = false;
        switch (state) {
            case State::NotStarted:
                set_state(State::BeforeFall, flag);
                player->start_animation(this);
                donkey_kong->start_animation(this);
                pauline->start_animation(this);
                for (unsigned int i = 0; i < lower_falling_girders.size(); ++i) {
                    lower_falling_girders[i]->set_left(
                        {lower_falling_girders[i]->get_left().x,
                         -constants::GIRDER_THICKNESS * (i + constants::STAGE_100M_LOWER_GIRDER_HIDE_OFFSET)});
                    lower_falling_girders[i]->set_right(
                        {lower_falling_girders[i]->get_right().x,
                         -constants::GIRDER_THICKNESS * (i + constants::STAGE_100M_LOWER_GIRDER_HIDE_OFFSET)});
                }
                upper_falling_girder->set_left({upper_falling_girder->get_left().x, constants::STAGE_100M_HIDDEN_GIRDER_Y});
                upper_falling_girder->set_right({upper_falling_girder->get_right().x, constants::STAGE_100M_HIDDEN_GIRDER_Y});
                break;
            case State::BeforeFall:
                if (time_elapsed_in_state < constants::STAGE_100M_BEFORE_FALL_DURATION) {
                    break;
                }
                set_state(State::Falling, flag);
                break;
            case State::Falling:
                donkey_kong->set_position(donkey_kong->get_position() + sf::Vector2f(0.f, constants::STAGE_100M_FALLING_SPEED * dt));
                if (donkey_kong->get_position().y < constants::STAGE_100M_IMPACT_Y) {
                    break;
                }
                set_state(State::Impact, flag);
                donkey_kong->set_position({donkey_kong->get_position().x, constants::STAGE_100M_IMPACT_Y});
                break;
            case State::Impact:
                if (time_elapsed_in_state < constants::STAGE_100M_IMPACT_DURATION) {
                    break;
                }
                set_state(State::United, flag);
                upper_falling_girder->set_left({upper_falling_girder->get_left().x, constants::STAGE_100M_FINAL_PLATFORM_Y});
                upper_falling_girder->set_right({upper_falling_girder->get_right().x, constants::STAGE_100M_FINAL_PLATFORM_Y});
                pauline->set_position({constants::STAGE_100M_FINAL_PAULINE_X, constants::STAGE_100M_FINAL_PLATFORM_Y});
                player->enter_platform(upper_falling_girder, constants::VIEW_WIDTH - constants::STAGE_100M_FINAL_PLAYER_RIGHT_MARGIN);
                player->set_facing_right(false);
                break;
            case State::United:
                if (time_elapsed_in_state < constants::STAGE_100M_UNITED_DURATION) {
                    break;
                }
                set_state(State::Finished, flag);
                break;
            case State::Finished:
                return;
        }
    }
}
