#include "PlatformComponentRepository.hpp"

/**
 * @brief Finds a platform directly below the provided world position.
 */
std::shared_ptr<Platform> PlatformComponentRepository::find_platform_underneath(const sf::Vector2f &position, float h_tolerance, float snap_distance) {
    for (auto it = begin(); it != end(); ++it) {
        auto platform = it->second->get_entity();
        
        if (platform->covers_x(position.x, h_tolerance)) {
            float surface_y = platform->surface_y_at(position.x);
            if (position.y > surface_y && position.y < surface_y + snap_distance) {  // remember that y increases downward in SFML coordinates // TODO: change origin of Barrel
                return platform;
            }
        }
    }
    return std::shared_ptr<Platform>();
}
