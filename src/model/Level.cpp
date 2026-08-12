#include "Level.hpp"

/**
 * @brief Creates a level and initializes the tracked repositories.
 */
Level::Level(Id id_generator()) : entities(id_generator), updatable_components(entities), platform_components(entities), climbable_components(entities), player(entities.add_player()) {}

/**
 * @brief Advances the level simulation by one tick.
 * @param dt Time step in seconds.
 */
void Level::update(float dt) {
    entities.handle_deletions();
    updatable_components.update_all(dt, *this);
}
