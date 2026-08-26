#include "DK/model/components/PickableComponentRepository.hpp"

#include "DK/model/components/PickableComponentFactory.hpp"

std::unique_ptr<Component<Pickable>> PickableComponentFactory::create_component_for(std::shared_ptr<BaseEntity> entity) {
    return entity->create_pickable_component();
}

std::shared_ptr<Pickable> PickableComponentRepository::find_touching_pickable(const sf::RectangleShape &player_shape) {
    for (auto it = begin(); it != end(); ++it) {
        auto pickable = it->second->get_entity();
        if (pickable->touches(player_shape)) {
            return pickable;
        }
    }
    return nullptr;
}
