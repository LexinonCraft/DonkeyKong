#include "PlatformComponentRepository.hpp"

std::shared_ptr<Platform> PlatformComponentRepository::find_platform_underneath(const sf::Vector2f &position, float snap_distance) {
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
