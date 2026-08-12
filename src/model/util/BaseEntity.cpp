#include <stdexcept>

#include "BaseEntity.hpp"
#include "EntityRepository.hpp"

void BaseEntity::destroy() {
    if (!destroyed) {
        ref.get_repository().prepare_for_deletion(ref.get_id());
        destroyed = true;
    }
}

void BaseEntity::assert_alive() const {
    if (destroyed) {
        throw std::runtime_error("Entity is destroyed but expected to be alive.");
    }
}
