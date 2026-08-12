#include <stdexcept>

#include "BaseEntity.hpp"
#include "EntityRepository.hpp"

/**
 * @brief Schedules the entity for deletion in the owning repository.
 */
void BaseEntity::destroy() {
    if (!destroyed) {
        ref.get_repository().prepare_for_deletion(ref.get_id());
        destroyed = true;
    }
}

/**
 * @brief Ensures the entity is still valid before it is used.
 */
void BaseEntity::assert_alive() const {
    if (destroyed) {
        throw std::runtime_error("Entity is destroyed but expected to be alive.");
    }
}
