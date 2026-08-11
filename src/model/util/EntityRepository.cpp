#include "EntityRepository.hpp"

void EntityRepository::handle_deletions() {
    while (!pending_deletions.empty()) {
        Id id = pending_deletions.front();
        pending_deletions.pop();

        auto it = entities.find(id);
        if (it != entities.end()) {
            for (auto obs_it = observers.begin(); obs_it != observers.end(); ++obs_it) {
                obs_it->second->on_entity_removed(it->second);
            }
            entities.erase(it);
        }
    }

    for (auto it = entities.begin(); it != entities.end(); ++it) {
        it->second->check_referenced_entities();
    }
}
