#include "UpdatableComponentRepository.hpp"

void UpdatableComponentRepository::update_all(float dt, Level &level) {
    for (auto it = begin(); it != end(); ++it) {
        it->second->get_entity()->update(dt, level);
    }
}
