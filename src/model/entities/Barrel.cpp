#include "Barrel.hpp"

#include <SFML/Graphics/Color.hpp>
#include <memory>

#include "../Constants.hpp"
#include "../Level.hpp"
#include "../components/Platform.hpp"
#include "../components/PlatformComponentRepository.hpp"
#include "../util/EntityVisitor.hpp"

#include <iostream>

Barrel::Barrel(Ref ref, sf::Vector2f position) :
    BaseEntity(ref),
    position(position),
    shape(constants::BARREL_RADIUS) {
        // origin at the circle's centre so `position` is the barrel's centre
        shape.setOrigin({constants::BARREL_RADIUS, constants::BARREL_RADIUS});
        shape.setFillColor(sf::Color(120, 200, 230)); // light blue, stands out on the red girders
        shape.setPosition(position);
}

void Barrel::set_on_platform(std::weak_ptr<Platform> platform) {
    auto platform_locked = platform.lock();
    if (!platform_locked)
        return;
    vx = constants::ROLL_SPEED * static_cast<float>(platform_locked->downhill_sign());
    current_platform = platform;
    vy = 0.f;
}

void Barrel::update(float dt, Level &level) {
    if (get_state() == State::OnGirder) {
        position.x += vx * dt;
        auto platform = current_platform.lock();
        if (platform && platform->covers_x(position.x)) {
            // stay glued to the surface: height follows the slope (tan angle)
            position.y = platform->surface_y_at(position.x) - constants::BARREL_RADIUS;
        } else {
            // rolled off the lower end -> drop straight down off the ledge.
            current_platform.reset();
            vx = 0.f;
            vy = 0.f;
        }
    } else { // Falling
        vy += constants::GRAVITY * dt;
        position.x += vx * dt;
        position.y += vy * dt;
        check_platform_intersection(level.get_platforms());
    }

    // No respawn here: once the barrel rolls off the last girder it just keeps
    // falling. BarrelControl notices it has left the stage and replaces it.
    shape.setPosition(position);
}

void Barrel::accept(EntityVisitor &visitor) {
    visitor.visit(*this);
}

void Barrel::check_platform_intersection(PlatformComponentRepository &platforms) {
    set_on_platform(platforms.find_platform_underneath({position.x, position.y}, constants::BARREL_RADIUS));
}
