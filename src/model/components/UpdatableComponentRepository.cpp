#include "DK/model/components/UpdatableComponentRepository.hpp"

#include "DK/model/components/UpdatableComponentFactory.hpp"

std::unique_ptr<Component<Updatable>> UpdatableComponentFactory::create_component_for(std::shared_ptr<BaseEntity> entity) {
    return entity->create_updatable_component();
}

UpdatableComponentRepository::UpdatableComponentRepository(EntityRepository &entity_repo)
    : ComponentRepository<Component<Updatable>>(entity_repo, std::make_unique<UpdatableComponentFactory>()) {}

void UpdatableComponentRepository::update_all(float dt, Stage &stage) {
    iterating = true;
    for (auto it = begin(); it != end(); ++it) {
        it->second->get_entity()->update(dt, stage);
    }
    iterating = false;
}
