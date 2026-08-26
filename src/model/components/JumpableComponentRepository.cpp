#include "DK/model/components/JumpableComponentRepository.hpp"

#include "DK/model/components/JumpableComponentFactory.hpp"

std::unique_ptr<Component<Jumpable>> JumpableComponentFactory::create_component_for(std::shared_ptr<BaseEntity> entity) {
    return entity->create_jumpable_component();
}

void JumpableComponentRepository::check_all_jumpables(const Player &player, Stage &stage) {
    for (auto it = begin(); it != end(); ++it) {
        it->second->get_entity()->check_jumps_over(player, stage);
    }
}
