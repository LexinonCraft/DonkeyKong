#ifndef PLATFORM_COMPONENT_REPOSITORY_HPP
#define PLATFORM_COMPONENT_REPOSITORY_HPP

#include <memory>

#include "DK/model/components/Platform.hpp"
#include "DK/model/util/Component.hpp"
#include "DK/model/util/ComponentRepository.hpp"

/**
 * @brief Repository for platform behaviour components.
 *
 * It exposes geometry queries so game objects can determine whether they are on,
 * below, or above a platform at a given world position.
 */
class PlatformComponentRepository : public ComponentRepository<Component<Platform>> {
public:
    /**
     * @brief Creates the repository and registers it with the entity repository.
     * @param repository Entity repository to observe.
     */
    explicit PlatformComponentRepository(EntityRepository &repository);

    /**
     * @brief Finds a platform directly underneath a world position.
     * @param position Position to inspect.
     * @param h_tolerance_left Horizontal tolerance at the platform's left edge.
     * @param h_tolerance_right Horizontal tolerance at the platform's right edge.
     * @param snap_distance Vertical search distance.
     * @returns Matching platform or an empty pointer if nothing is found.
     */
    std::shared_ptr<Platform> find_platform_underneath(const sf::Vector2f &position, float h_tolerance_left, float h_tolerance_right,
                                                       float snap_distance);

    /**
     * @brief Finds a platform directly underneath a world position.
     * @param position Position to inspect.
     * @param h_tolerance_left Horizontal tolerance at the platform's left edge.
     * @param h_tolerance_right Horizontal tolerance at the platform's right edge.
     * @param snap_distance Vertical search distance.
     * @param exclude_platform Platform to exclude from the search
     * @returns Matching platform or an empty pointer if nothing is found.
     */
    std::shared_ptr<Platform> find_platform_underneath(const sf::Vector2f &position, float h_tolerance_left, float h_tolerance_right,
                                                       float snap_distance, std::shared_ptr<Platform> exclude_platform);
};

#endif
