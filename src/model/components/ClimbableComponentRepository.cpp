#include "DK/model/components/ClimbableComponentRepository.hpp"

#include "DK/model/components/ClimbableComponentFactory.hpp"

std::unique_ptr<Component<Climbable>> ClimbableComponentFactory::create_component_for(std::shared_ptr<BaseEntity> entity) {
    return entity->create_climbable_component();
}

ClimbableComponentRepository::ClimbableComponentRepository(EntityRepository &repository)
    : ComponentRepository<Component<Climbable>>(repository, std::make_unique<ClimbableComponentFactory>()) {}

std::shared_ptr<Climbable> ClimbableComponentRepository::find_climbable_up_at(const sf::Vector2f &position, float h_tolerance,
                                                                              float v_tolerance) {
    for (auto it = begin(); it != end(); ++it) {
        auto climbable = it->second->get_entity();
        if (climbable->can_climb_up(position, h_tolerance, v_tolerance)) {
            return climbable;
        }
    }
    return std::shared_ptr<Climbable>();
}

std::shared_ptr<Climbable> ClimbableComponentRepository::find_climbable_down_at(const sf::Vector2f &position, float h_tolerance,
                                                                                float v_tolerance) {
    for (auto it = begin(); it != end(); ++it) {
        auto climbable = it->second->get_entity();
        if (climbable->can_climb_down(position, h_tolerance, v_tolerance)) {
            return climbable;
        }
    }
    return std::shared_ptr<Climbable>();
}
