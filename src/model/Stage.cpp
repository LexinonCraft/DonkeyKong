#include <algorithm>

#include "Stage.hpp"
#include "PlayerData.hpp"
#include "StageSequence.hpp"
#include "animations/PlayerDeathAnimation.hpp"

namespace {
float calculate_barrel_difficulty_multiplier(unsigned int level) {
    return std::min(
        1.f + static_cast<float>(level) * constants::BARREL_DIFFICULTY_INCREASE_PER_LEVEL,
        constants::BARREL_MAX_DIFFICULTY_MULTIPLIER);
}
}

/**
 * @brief Creates a level and initializes the tracked repositories.
 */
Stage::Stage(int rng(), PlayerData &player_data) : rng(rng), entities(rng), updatable_components(entities), platform_components(entities), climbable_components(entities), enemy_components(entities), pickable_components(entities), player(entities.add_player()), player_data(player_data) {}

/**
 * @brief Advances the level simulation by one tick.
 * @param dt Time step in seconds.
 */
void Stage::update(float dt) {
    entities.handle_additions();
    entities.handle_deletions();

    if (!current_animation) {
        update_while_running(dt);
    } else {
        current_animation->update(dt);
        if (current_animation->check_finished()) {
            // TODO
        }
    }
}

void Stage::on_player_dying() {
    if (current_animation)
        return;
    
    player_died = true;
    current_animation = std::make_unique<PlayerDeathAnimation>(*this, player);
}

void Stage::on_completed() {
    if (current_animation)
        return;
}

float Stage::get_barrel_roll_speed() const {
    return constants::ROLL_SPEED * get_barrel_difficulty_multiplier();
}

float Stage::get_barrel_difficulty_multiplier() const {
    return calculate_barrel_difficulty_multiplier(player_data.get_level());
}

void Stage::update_while_running(float dt) {
    time_elapsed += dt;
    updatable_components.update_all(dt, *this);
}

bool Stage::check_over() {
    if (!(current_animation && current_animation->is_exit_animation() && current_animation->check_finished())) {
        return false;
    }

    if (player_died) {
        player_data.lose_life();
    } else {
        advance_stage(player_data);
    }
    on_exit();
    return true;
}
