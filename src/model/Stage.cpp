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
Stage::Stage(int rng(), PlayerData &player_data) : rng(rng), entities(rng), updatable_components(entities), platform_components(entities), climbable_components(entities), enemy_components(entities), jumpable_components(entities), pickable_components(entities), observer_registry(rng), player(entities.add_player()), player_data(player_data) {}

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
        if (current_animation->is_finished() && !current_animation->is_exit_animation()) {
            current_animation.reset();
        }
    }

    if (current_animation && current_animation->is_exit_animation() && current_animation->is_finished() && !ran_on_exit) {
        on_exit();
        ran_on_exit = true;
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

void Stage::on_completed() {
    if (current_animation)
        return;
}

void Stage::add_to_score(sf::Vector2f position, int score_to_add) {
    if (current_animation)
        return;

    player_data.add_to_score(score_to_add);
    for (auto it = observer_registry.begin(); it != observer_registry.end(); ++it) {
        it->second->on_score_added(position, score_to_add);
    }
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

bool Stage::is_over() {
    return ran_on_exit;
}

void Stage::on_exit() {
    if (player_died) {
        player_data.lose_life();
    } else {
        advance_stage(player_data);
    }
}

void Stage::clear_secondary_entities() {
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        if (it->second->is_secondary_entity()) {
            it->second->destroy();
        }
    }

    // Remove all secondary entities from the pending additions queue by rebuilding it without the secondary entities
    auto pending_additions = entities.get_pending_additions();
    std::queue<std::shared_ptr<BaseEntity>> temp_queue;
    while (!pending_additions.empty()) {
        auto entity = pending_additions.front();
        pending_additions.pop();
        if (!entity->is_secondary_entity()) {
            temp_queue.push(entity);
        }
    }
    pending_additions = std::move(temp_queue);
}
