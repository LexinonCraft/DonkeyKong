#include "DK/model/components/JumpableComponentRepository.hpp"

#include "DK/model/components/JumpableComponentFactory.hpp"

std::unique_ptr<Component<Jumpable>> JumpableComponentFactory::create_component_for(std::shared_ptr<BaseEntity> entity) {
    return entity->create_jumpable_component();
}

JumpableComponentRepository::JumpableComponentRepository(EntityRepository &entity_repo)
    : ComponentRepository<Component<Jumpable>>(entity_repo, std::make_unique<JumpableComponentFactory>()) {}

void JumpableComponentRepository::check_all_jumpables(const Player &player, Stage &stage) {
    for (auto it = begin(); it != end(); ++it) {
        it->second->get_entity()->check_jumps_over(player, stage);
    }
}
