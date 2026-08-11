#include "BaseEntity.hpp"
#include "EntityRepository.hpp"

void BaseEntity::destroy() {
    if (!destroyed) {
        ref.get_repository().prepare_for_deletion(ref.get_id());
        destroyed = true;
    }
}
