#include "Stage.hpp"
#include "PlayerData.hpp"

/**
 * @brief Creates a level and initializes the tracked repositories.
 */
Stage::Stage(Id id_generator(), PlayerData &player_data) : entities(id_generator), updatable_components(entities), platform_components(entities), climbable_components(entities), enemy_components(entities), player(entities.add_player()), player_data(player_data) {}

/**
 * @brief Advances the level simulation by one tick.
 * @param dt Time step in seconds.
 */
void Stage::update(float dt) {
    if (state != StageState::Running) {
        time_since_state_change += dt;
    }
    if (state == StageState::PlayerDying && time_since_state_change >= constants::PLAYER_DEATH_DURATION) {
        state = StageState::PlayerDead;
    }

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
    player_data.lose_life();
}

void Stage::update_while_running(float dt) {
    time_elapsed += dt;
    updatable_components.update_all(dt, *this);
}
