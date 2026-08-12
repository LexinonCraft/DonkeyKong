#include "UpdatableComponentRepository.hpp"

/**
 * @brief Updates all active updatable entities in the level.
 * @param dt Time step in seconds.
 * @param level Current level state used during the updates.
 */
void UpdatableComponentRepository::update_all(float dt, Level &level) {
    for (auto it = begin(); it != end(); ++it) {
        it->second->get_entity()->update(dt, level);
    }
}
