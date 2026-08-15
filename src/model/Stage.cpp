#include "Stage.hpp"

/**
 * @brief Creates a level and initializes the tracked repositories.
 */
Stage::Stage(Id id_generator(), PlayerData &player_data) : entities(id_generator), updatable_components(entities), platform_components(entities), climbable_components(entities), player(entities.add_player()), player_data(player_data) {}

/**
 * @brief Advances the level simulation by one tick.
 * @param dt Time step in seconds.
 */
void Stage::update(float dt) {
    entities.handle_deletions();
    updatable_components.update_all(dt, *this);
}
