#include "DK/model/components/ClimbableComponentRepository.hpp"

/**
 * @brief Finds a climbable object that an object at the given position can climb upward from.
 */
std::shared_ptr<Climbable> ClimbableComponentRepository::find_climbable_up_at(const sf::Vector2f &position, float h_tolerance, float v_tolerance) {
    for (auto it = begin(); it != end(); ++it) {
        auto climbable = it->second->get_entity();
        if (climbable->can_climb_up(position, h_tolerance, v_tolerance)) {
            return climbable;
        }
    }
    return std::shared_ptr<Climbable>();
}

/**
 * @brief Finds a climbable object that an object at the given position can climb downward from.
 */
std::shared_ptr<Climbable> ClimbableComponentRepository::find_climbable_down_at(const sf::Vector2f &position, float h_tolerance, float v_tolerance) {
    for (auto it = begin(); it != end(); ++it) {
        auto climbable = it->second->get_entity();
        if (climbable->can_climb_down(position, h_tolerance, v_tolerance)) {
            return climbable;
        }
    }
    return std::shared_ptr<Climbable>();
}
