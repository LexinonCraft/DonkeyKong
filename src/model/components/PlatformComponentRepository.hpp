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

    std::shared_ptr<Platform> find_platform_underneath(const sf::Vector2f &position, float snap_distance) {
        for (auto it = begin(); it != end(); ++it) {
            auto platform = it->second->get_entity();
            
            if (platform->covers_x(position.x)) {
                float surface_y = platform->surface_y_at(position.x);
                if (position.y < surface_y && surface_y < position.y + snap_distance) {  // remember that y increases downward in SFML coordinates // TODO: change origin of Barrel
                    return platform;
                }
            }
        }
        return std::shared_ptr<Platform>();
    }
};

#endif
