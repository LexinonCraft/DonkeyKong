#include "Barrel.hpp"

#include <memory>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "../../Constants.hpp"
#include "../Stage.hpp"
#include "../components/Platform.hpp"
#include "../components/PlatformComponentRepository.hpp"
#include "../util/EntityVisitor.hpp"

Barrel::Barrel(Ref ref, sf::Vector2f position) :
    BaseEntity(ref),
    position(position),
    shape(constants::BARREL_RADIUS) {
        // origin at the circle's centre so `position` is the barrel's centre
        shape.setOrigin({constants::BARREL_RADIUS, 2 * constants::BARREL_RADIUS});
        shape.setFillColor(sf::Color(120, 200, 230)); // light blue, stands out on the red girders
        shape.setPosition(position);
}

void Barrel::set_on_platform(std::shared_ptr<Platform> platform, float roll_speed) {
    if (!platform)
        return;
    vx = roll_speed * static_cast<float>(platform->downhill_sign());
    state = State::OnGirder;
    current_platform = platform;
    vy = 0.f;
}

void Barrel::update(float dt, Stage &level) {
    switch (state) {
        case State::OnGirder:
            position.x += vx * dt;
            roll_distance += vx * dt * constants::BARREL_PLATFORM_ROLL_DISTANCE_FACTOR;
            if (current_platform && current_platform->covers_x(position.x, constants::BARREL_RADIUS, constants::BARREL_RADIUS)) {
                // stay glued to the surface: height follows the slope (tan angle)
                position.y = current_platform->surface_y_at(position.x);

                if (current_climbable) {
                    if (roll_down_climbable && ((vx < 0 && position.x < current_climbable->get_x_pos()) || (vx > 0 && position.x > current_climbable->get_x_pos()))) {
                        vx = 0;
                        position.x = current_climbable->get_x_pos();
                        position.y = current_climbable->get_upper_y_pos();
                        state = State::RollingDownClimbable;
                        roll_distance = 0.f;
                    } else if ((vx < 0 && position.x < current_climbable->get_x_pos() - constants::BARREL_RADIUS) || (vx > 0 && position.x > current_climbable->get_x_pos() + constants::BARREL_RADIUS)) {
                        current_climbable.reset();
                    }
                } else {
                    current_climbable = level.get_climbables().find_climbable_down_at(position, constants::BARREL_RADIUS, constants::BARREL_RADIUS);
                    if (current_climbable) {
                        roll_down_climbable = level.random_int() % 2 == 0;
                    }
                }
            } else {
                const std::shared_ptr<Platform> platform_below = level.get_platforms().find_platform_underneath(position, constants::BARREL_RADIUS, constants::BARREL_RADIUS, constants::SEAM_SNAP_DISTANCE);
                if (platform_below) {
                    set_on_platform(platform_below, level.get_barrel_roll_speed());
                    current_climbable.reset();
                    position.y = current_platform->surface_y_at(position.x);
                } else {
                    state = State::Falling;
                    current_climbable.reset();
                    vx = 0.f;
                    vy = 0.f;
                }
            }
            break;
        case State::Falling:
            vy += constants::GRAVITY * dt;
            check_platform_intersection(level.get_platforms(), dt, level.get_barrel_roll_speed());
            position.x += vx * dt;
            position.y += vy * dt;
            break;
        case State::RollingDownClimbable:
            vy = level.get_barrel_roll_speed();
            if (position.y < current_climbable->get_lower_y_pos()) {
                position.y += vy * dt;
                roll_distance += vy * dt * constants::BARREL_CLIMBABLE_ROLL_DISTANCE_FACTOR;
            } else {
                set_on_platform(current_climbable->get_lower_end(), level.get_barrel_roll_speed());
                current_climbable.reset();
                position.x += vx * dt;
                position.y += vy * dt;
                roll_distance = 0.f;
            }
            break;
    }

    if (position.y > constants::BARREL_RADIUS) {
        destroy();
    }

    shape.setPosition(position);
}

void Barrel::accept(EntityVisitor &visitor) {
    visitor.visit(*this);
}

bool Barrel::touches(const sf::RectangleShape &player_shape) const {
    return shape.getGlobalBounds().findIntersection(player_shape.getGlobalBounds()).has_value();
}

void Barrel::check_platform_intersection(PlatformComponentRepository &platforms, float dt, float roll_speed) {
    set_on_platform(platforms.find_platform_underneath({position.x, position.y}, constants::BARREL_RADIUS, constants::BARREL_RADIUS, platform_snap_distance(dt)), roll_speed);
}

void Barrel::check_referenced_entities() {
    handle_destroyed_indirect(current_platform);
}

float Barrel::platform_snap_distance(float dt) const {
    float distance = vy * dt;
    if (distance > constants::PLATFORM_MINIMUM_SNAP_DISTANCE) {
        return distance;
    } else {
        return constants::PLATFORM_MINIMUM_SNAP_DISTANCE;
    }
}
