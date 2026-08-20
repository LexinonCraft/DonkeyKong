#include <stdexcept>

#include "DonkeyKong.hpp"
#include "../components/Platform.hpp"
#include "../Stage.hpp"

DonkeyKong::DonkeyKong(Ref ref, std::shared_ptr<Platform> platform, float x_position, bool throw_barrels)
    : BaseEntity(ref), Updatable(), Enemy(), position(x_position, platform->surface_y_at(x_position)), platform(platform), throw_barrels(throw_barrels) {
    state = State::Idle;
    idle_countdown = constants::DONKEY_KONG_MIN_IDLE_DURATION;
} 

void DonkeyKong::update(float dt, Stage &stage) {
    switch (state) {
        case State::Idle:
            idle_countdown -= dt;
            if (idle_countdown <= 0.f) {
                unsigned int next_action;
                if (consecutive_angry_actions >= constants::DONKEY_KONG_MAX_CONSECUTIVE_ANGRY_ACTIONS) {
                    next_action = 0; // Force throwing barrel
                } else {
                    next_action = stage.random_int() % 3;
                }
                switch (next_action) {
                    case 0:
                    case 1:
                        state = State::ThrowingBarrel;
                        num_barrels_to_be_thrown = stage.random_int() % constants::MAX_BARRELS_THROWN + 1;
                        consecutive_angry_actions = 0;
                        break;
                    case 2:
                        state = State::Angry;
                        angry_animation_frames = stage.random_int() % (constants::DONKEY_KONG_MAX_ANGRY_ANIMATION_FRAMES - constants::DONKEY_KONG_MIN_ANGRY_ANIMATION_FRAMES + 1) + constants::DONKEY_KONG_MIN_ANGRY_ANIMATION_FRAMES;
                        consecutive_angry_actions++;
                        break;
                    default:
                        throw std::logic_error("Invalid random state for DonkeyKong");
                        break;
                }
                action_timer = 0.f;
            }
            break;

        case State::ThrowingBarrel:
            action_timer += dt;
            if (num_barrels_to_be_thrown > 0 && action_timer >= constants::BARREL_THROW_ANIMATION_INTERVAL * 2) {
                float barrel_x_pos = position.x + constants::BARREL_THROW_OFFSET_X;
                auto barrel = stage.get_entities().add_barrel({barrel_x_pos, platform->surface_y_at(barrel_x_pos)});
                barrel->set_on_platform(platform, 1);
                num_barrels_to_be_thrown--;
                action_timer -= constants::BARREL_THROW_ANIMATION_INTERVAL * 4;
            }
            if (num_barrels_to_be_thrown == 0 && action_timer >= 0) {
                switch_to_idle(stage.random_int());
            }
            break;

        case State::Angry:
            action_timer += dt;
            if (action_timer >= constants::DONKEY_KONG_ANGRY_ANIMATION_INTERVAL * angry_animation_frames) {
                switch_to_idle(stage.random_int());
            }
            break;
    }
}

void DonkeyKong::switch_to_idle(int random_int) {
    state = State::Idle;
    idle_countdown = constants::DONKEY_KONG_MIN_IDLE_DURATION + (random_int % constants::DONKEY_KONG_IDLE_DURATION_STEPS) * 
                     ((constants::DONKEY_KONG_MAX_IDLE_DURATION - constants::DONKEY_KONG_MIN_IDLE_DURATION) / constants::DONKEY_KONG_IDLE_DURATION_STEPS);
}
