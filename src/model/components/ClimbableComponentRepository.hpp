#ifndef CLIMBABLE_COMPONENT_REPOSITORY_HPP
#define CLIMBABLE_COMPONENT_REPOSITORY_HPP

#include <memory>

#include "../util/ComponentRepository.hpp"
#include "../util/Component.hpp"
#include "ClimbableComponentFactory.hpp"
#include "Climbable.hpp"

class ClimbableComponentRepository : public ComponentRepository<Component<Climbable>> {
public:
    ClimbableComponentRepository(EntityRepository &repository) : ComponentRepository<Component<Climbable>>(repository, std::make_unique<ClimbableComponentFactory>()) {}

    std::shared_ptr<Climbable> find_climbable_up_at(const sf::Vector2f &position, float h_tolerance, float v_tolerance);

    std::shared_ptr<Climbable> find_climbable_down_at(const sf::Vector2f &position, float h_tolerance, float v_tolerance);
};

#endif
