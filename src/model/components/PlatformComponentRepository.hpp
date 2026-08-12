#ifndef PLATFORM_COMPONENT_REPOSITORY_HPP
#define PLATFORM_COMPONENT_REPOSITORY_HPP

#include <memory>

#include "../util/ComponentRepository.hpp"
#include "../util/Component.hpp"
#include "PlatformComponentFactory.hpp"
#include "Platform.hpp"

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
    PlatformComponentRepository(EntityRepository &repository) : ComponentRepository<Component<Platform>>(repository, std::make_unique<PlatformComponentFactory>()) {}

    /**
     * @brief Finds a platform directly underneath a world position.
     * @param position Position to inspect.
     * @param snap_distance Vertical search distance.
     * @return Matching platform or an empty pointer if nothing is found.
     */
    std::shared_ptr<Platform> find_platform_underneath(const sf::Vector2f &position, float snap_distance);
};

#endif
