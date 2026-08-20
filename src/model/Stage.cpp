#include <stdexcept>

#include "Stage.hpp"
#include "PlayerData.hpp"
#include "StageSequence.hpp"

/**
 * @brief Creates a level and initializes the tracked repositories.
 */
Stage::Stage(int rng(), PlayerData &player_data) : rng(rng), entities(rng), updatable_components(entities), platform_components(entities), climbable_components(entities), enemy_components(entities), jumpable_components(entities), observer_registry(rng), player(entities.add_player()), player_data(player_data) {}

/**
 * @brief Advances the level simulation by one tick.
 * @param dt Time step in seconds.
 */
void Stage::update(float dt) {
    if (state != StageState::Running) {
        time_since_state_change += dt;
    }

    entities.handle_additions();
    entities.handle_deletions();

    if (state == StageState::Running) {
        update_while_running(dt);
    }
}

void Stage::on_player_dying() {
    if (state != StageState::Running)
        return;
    
    state = StageState::PlayerDying;
    time_since_state_change = 0.f;
}

void Stage::on_completed() {
    if (state != StageState::Running)
        return;

    state = StageState::Completed;
    time_since_state_change = 0.f;
}

bool Stage::on_exit() {
    switch (state) {
        case StageState::Running:
            throw std::runtime_error("Cannot exit stage while running");
        case StageState::PlayerDying:
            if (player_data.lose_life()) {
                return true;
            } else {
                return false;
            }
        case StageState::Completed:
            advance_stage(player_data);
            return true;
        default:
            throw std::runtime_error("Unknown stage state");
    }
}

void Stage::add_to_score(sf::Vector2f position, int score_to_add) {
    player_data.add_to_score(score_to_add);
    for (auto it = observer_registry.begin(); it != observer_registry.end(); ++it) {
        it->second->on_score_added(position, score_to_add);
    }
}

void Stage::update_while_running(float dt) {
    time_elapsed += dt;
    updatable_components.update_all(dt, *this);
}
