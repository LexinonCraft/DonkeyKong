#include "DK/model/Stage.hpp"

#include <algorithm>

#include "DK/model/PlayerData.hpp"
#include "DK/model/StageSequence.hpp"
#include "DK/model/animations/PlayerDeathAnimation.hpp"

namespace {
/** @brief Calculates the barrel difficulty multiplier based on the current level. */
float calculate_barrel_difficulty_multiplier(unsigned int level) {
    return std::min(1.f + static_cast<float>(level) * constants::BARREL_DIFFICULTY_INCREASE_PER_LEVEL,
                    constants::BARREL_MAX_DIFFICULTY_MULTIPLIER);
}
} // namespace

Stage::Stage(int rng(), PlayerData &player_data)
    : rng(rng), entities(rng), updatable_components(entities), platform_components(entities), climbable_components(entities),
      enemy_components(entities), jumpable_components(entities), pickable_components(entities), observer_registry(rng),
      player(entities.add_player()), player_data(player_data) {}

void Stage::update(float dt) {
    // Handle additions and deletions of entities outside of the update loop so we don't invalidate iterators.
    entities.handle_additions();
    entities.handle_deletions();

    if (!current_animation) {
        update_while_running(dt);
    } else {
        current_animation->update(dt);
        if (!current_animation->is_finished())
            return;

        // the animation is finished, so we either run the exit logic or reset the animation pointer
        if (current_animation->is_exit_animation()) {
            if (!ran_on_exit) {
                on_exit();
                ran_on_exit = true;
            }
        } else {
            current_animation.reset();
        }
    }
}

void Stage::on_player_dying() {
    if (current_animation)
        return;

    player_died = true;
    current_animation = std::make_unique<PlayerDeathAnimation>(*this, player);
    for (auto it = observer_registry.begin(); it != observer_registry.end(); ++it) {
        it->second->on_player_died();
    }
}

void Stage::add_to_score(sf::Vector2f position, int score_to_add) {
    if (current_animation)
        return;

    player_data.add_to_score(score_to_add);
    for (auto it = observer_registry.begin(); it != observer_registry.end(); ++it) {
        it->second->on_score_added(position, score_to_add);
    }
}

float Stage::get_barrel_roll_speed() const { return constants::ROLL_SPEED * get_barrel_difficulty_multiplier(); }

float Stage::get_barrel_difficulty_multiplier() const { return calculate_barrel_difficulty_multiplier(player_data.get_level()); }

void Stage::update_while_running(float dt) {
    time_elapsed += dt;
    updatable_components.update_all(dt, *this);
}

void Stage::on_exit() {
    if (player_died) {
        player_data.lose_life();
    } else {
        advance_stage(player_data);
    }
}
