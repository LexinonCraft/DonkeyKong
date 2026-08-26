#ifndef CLIMBABLE_COMPONENT_REPOSITORY_HPP
#define CLIMBABLE_COMPONENT_REPOSITORY_HPP

#include <memory>

#include "DK/model/components/Climbable.hpp"
#include "DK/model/util/Component.hpp"
#include "DK/model/util/ComponentRepository.hpp"

/**
 * @brief Repository storing climbable behaviour components.
 *
 * It provides helper queries to find the ladder or climbing structure closest to
 * a player position when moving up or down.
 */
class ClimbableComponentRepository : public ComponentRepository<Component<Climbable>> {
public:
    /**
     * @brief Creates the repository and registers it with the entity repository.
     * @param repository Entity repository to observe.
     */
    explicit ClimbableComponentRepository(EntityRepository &repository);

    /**
     * @brief Finds the nearest climbable that matches the player while moving upward.
     * @param position Player position.
     * @param h_tolerance Horizontal tolerance.
     * @param v_tolerance Vertical tolerance.
     * @returns Matching climbable, or an empty pointer if no match exists.
     */
    std::shared_ptr<Climbable> find_climbable_up_at(const sf::Vector2f &position, float h_tolerance, float v_tolerance);

    /**
     * @brief Finds the nearest climbable that matches the player while moving downward.
     * @param position Player position.
     * @param h_tolerance Horizontal tolerance.
     * @param v_tolerance Vertical tolerance.
     * @returns Matching climbable, or an empty pointer if no match exists.
     */
    std::shared_ptr<Climbable> find_climbable_down_at(const sf::Vector2f &position, float h_tolerance, float v_tolerance);
};

#endif
