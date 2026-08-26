#include "DK/model/components/UpdatableComponentRepository.hpp"

void UpdatableComponentRepository::update_all(float dt, Stage &level) {
    iterating = true;
    for (auto it = begin(); it != end(); ++it) {
        it->second->get_entity()->update(dt, level);
    }
    iterating = false;
}
