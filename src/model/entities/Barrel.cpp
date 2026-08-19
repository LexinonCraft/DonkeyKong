#include "Barrel.hpp"

#include <cmath>
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

void Barrel::set_on_platform(std::shared_ptr<Platform> platform, int roll_direction) {
    if (!platform)
        return;
    int platform_sign = platform->downhill_sign();
    vx = constants::ROLL_SPEED * static_cast<float>(platform_sign != 0 ? platform_sign : roll_direction);
    state = State::OnGirder;
    current_platform = platform;
    vy = 0.f;
}

void Barrel::update(float dt, Stage &level) {
    switch (state) {
        case State::OnGirder:
            position.x += vx * dt;
            roll_distance += vx * dt * constants::BARREL_PLATFORM_ROLL_DISTANCE_FACTOR;
            if (current_platform && current_platform->covers_x(position.x, platform_h_tolerance_left(), platform_h_tolerance_right())) {
                // stay glued to the surface: height follows the slope (tan angle)
                position.y = current_platform->surface_y_at(position.x);

                if (current_climbable) {
                    if (roll_down_climbable && ((vx < 0 && position.x < current_climbable->get_x_pos()) || (vx > 0 && position.x > current_climbable->get_x_pos()))) {
                        vx = 0;
                        vy = constants::ROLL_SPEED;
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
                const std::shared_ptr<Platform> platform_below = level.get_platforms().find_platform_underneath(position, platform_h_tolerance_left(), platform_h_tolerance_right(), constants::SEAM_SNAP_DISTANCE);
                if (platform_below) {
                    set_on_platform(platform_below, std::signbit(vx) ? -1 : 1);
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
            check_platform_intersection(level.get_platforms(), dt);
            position.x += vx * dt;
            position.y += vy * dt;
            break;
        case State::RollingDownClimbable:
            if (position.y < current_climbable->get_lower_y_pos()) {
                position.y += vy * dt;
                roll_distance += vy * dt * constants::BARREL_CLIMBABLE_ROLL_DISTANCE_FACTOR;
            } else {
                set_on_platform(current_climbable->get_lower_end());
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

void Barrel::check_platform_intersection(PlatformComponentRepository &platforms, float dt) {
    set_on_platform(platforms.find_platform_underneath({position.x, position.y}, platform_h_tolerance_left(), platform_h_tolerance_right(), platform_snap_distance(dt)));
}

void Barrel::check_referenced_entities() {
    handle_destroyed_indirect(current_platform);
}

float Barrel::platform_h_tolerance_left() const {
    if (vx > 0.f) {
        return constants::BARREL_RADIUS + vx * constants::PLATFORM_H_TOLERANCE_FACTOR;
    } else {
        return constants::BARREL_RADIUS;
    }
}

float Barrel::platform_h_tolerance_right() const {
    if (vx < 0.f) {
        return constants::BARREL_RADIUS + -vx * constants::PLATFORM_H_TOLERANCE_FACTOR;
    } else {
        return constants::BARREL_RADIUS;
    }
}

float Barrel::platform_snap_distance(float dt) const {
    float distance = vy * dt;
    if (distance > constants::PLATFORM_MINIMUM_SNAP_DISTANCE) {
        return distance;
    } else {
        return constants::PLATFORM_MINIMUM_SNAP_DISTANCE;
    }
}
