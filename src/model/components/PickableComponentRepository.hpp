#ifndef PICKABLE_COMPONENT_REPOSITORY_HPP
#define PICKABLE_COMPONENT_REPOSITORY_HPP

#include <memory>

#include "DK/model/components/Pickable.hpp"
#include "DK/model/util/Component.hpp"
#include "DK/model/util/ComponentRepository.hpp"

class PickableComponentRepository : public ComponentRepository<Component<Pickable>> {
public:
    explicit PickableComponentRepository(EntityRepository &repository);

    std::shared_ptr<Pickable> find_touching_pickable(const sf::RectangleShape &player_shape);
};

#endif
