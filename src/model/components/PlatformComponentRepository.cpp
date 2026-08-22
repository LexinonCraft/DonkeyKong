#include "DK/model/components/PlatformComponentRepository.hpp"

/**
 * @brief Finds a platform directly below the provided world position.
 */
std::shared_ptr<Platform> PlatformComponentRepository::find_platform_underneath(const sf::Vector2f &position, float h_tolerance_left,
                                                                                float h_tolerance_right, float snap_distance) {
    return find_platform_underneath(position, h_tolerance_left, h_tolerance_right, snap_distance, nullptr);
}

/**
 * @brief Finds a platform directly below the provided world position.
 */
std::shared_ptr<Platform> PlatformComponentRepository::find_platform_underneath(const sf::Vector2f &position, float h_tolerance_left,
                                                                                float h_tolerance_right, float snap_distance,
                                                                                std::shared_ptr<Platform> exclude_platform) {
    for (auto it = begin(); it != end(); ++it) {
        auto platform = it->second->get_entity();

        if (platform->is_active() && platform->covers_x(position.x, h_tolerance_left, h_tolerance_right)) {
            float surface_y = platform->surface_y_at(position.x);
            if (position.y + constants::PLATFORM_UNDERNEATH_OFFSET >= surface_y && position.y <= surface_y + snap_distance &&
                platform != exclude_platform) { // remember that y increases downward in SFML coordinates // TODO: change origin of Barrel
                return platform;
            }
        }
    }
    return std::shared_ptr<Platform>();
}
