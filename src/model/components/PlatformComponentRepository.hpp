#ifndef PLATFORM_COMPONENT_REPOSITORY_HPP
#define PLATFORM_COMPONENT_REPOSITORY_HPP

#include <memory>

#include "../util/ComponentRepository.hpp"
#include "../util/Component.hpp"
#include "PlatformComponentFactory.hpp"
#include "Platform.hpp"

class PlatformComponentRepository : public ComponentRepository<Component<Platform>> {
public:
    PlatformComponentRepository(EntityRepository &repository) : ComponentRepository<Component<Platform>>(repository, std::make_unique<PlatformComponentFactory>()) {}

    std::shared_ptr<Platform> find_platform_underneath(const sf::Vector2f &position, float snap_distance);
};

#endif
