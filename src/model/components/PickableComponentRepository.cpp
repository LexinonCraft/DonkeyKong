#include "DK/model/components/PickableComponentRepository.hpp"

std::shared_ptr<Pickable> PickableComponentRepository::find_touching_pickable(const sf::RectangleShape &player_shape) {
    for (auto it = begin(); it != end(); ++it) {
        auto pickable = it->second->get_entity();
        if (pickable->touches(player_shape)) {
            return pickable;
        }
    }
    return nullptr;
}
