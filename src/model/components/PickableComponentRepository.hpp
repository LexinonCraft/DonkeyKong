#ifndef PICKABLE_COMPONENT_REPOSITORY_HPP
#define PICKABLE_COMPONENT_REPOSITORY_HPP

#include <memory>

#include "DK/model/util/Component.hpp"
#include "DK/model/util/ComponentRepository.hpp"
#include "DK/model/components/Pickable.hpp"
#include "DK/model/components/PickableComponentFactory.hpp"

class PickableComponentRepository : public ComponentRepository<Component<Pickable>> {
public:
    PickableComponentRepository(EntityRepository &repository) : ComponentRepository<Component<Pickable>>(repository, std::make_unique<PickableComponentFactory>()) {}

    std::shared_ptr<Pickable> find_touching_pickable(const sf::RectangleShape &player_shape);
};

#endif
