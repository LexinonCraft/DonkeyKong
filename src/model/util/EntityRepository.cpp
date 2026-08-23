#include "DK/model/util/EntityRepository.hpp"

/**
 * @brief Adds all entities queued for insertion and notifies observers.
 */
void EntityRepository::handle_additions() {
    while (!pending_additions.empty()) {
        std::shared_ptr<BaseEntity> entity = pending_additions.front();
        pending_additions.pop();

        entities[entity->get_id()] = entity;

        for (auto it = observer_registry.begin(); it != observer_registry.end(); ++it) {
            it->second->on_entity_added(entity);
        }
    }
}

/**
 * @brief Removes all entities queued for deletion and refreshes remaining references.
 */
void EntityRepository::handle_deletions() {
    while (!pending_deletions.empty()) {
        Id id = pending_deletions.front();
        pending_deletions.pop();

        auto it = entities.find(id);
        if (it != entities.end()) {
            for (auto obs_it = observer_registry.begin(); obs_it != observer_registry.end(); ++obs_it) {
                obs_it->second->on_entity_removed(it->second);
            }
            entities.erase(it);
        }
    }

    for (auto it = entities.begin(); it != entities.end(); ++it) {
        it->second->check_referenced_entities();
    }
}
