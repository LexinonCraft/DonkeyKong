#include "DK/model/entities/Barrel.hpp"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <memory>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "DK/Constants.hpp"
#include "DK/model/PlayerData.hpp"
#include "DK/model/Stage.hpp"
#include "DK/model/components/Platform.hpp"
#include "DK/model/components/PlatformComponentRepository.hpp"
#include "DK/model/entities/Player.hpp"
#include "DK/model/util/EntityVisitor.hpp"
#include "DK/util/Math.hpp"

Barrel::Barrel(Ref ref, sf::Vector2f position) : BaseEntity(ref), position(position), shape(constants::BARREL_HITBOX_RADIUS) {
    // origin at the circle's centre so `position` is the barrel's centre
    shape.setOrigin({constants::BARREL_HITBOX_RADIUS, 2 * constants::BARREL_HITBOX_RADIUS});
    shape.setFillColor(sf::Color(120, 200, 230)); // light blue, stands out on the red girders
    shape.setPosition(position);
}

void Barrel::set_on_platform(std::shared_ptr<Platform> platform, float roll_speed, int roll_direction) {
    if (!platform)
        return;
    int platform_sign = platform->downhill_sign();
    int direction = platform_sign != 0 ? platform_sign : roll_direction;
    if (direction == 0)
        direction = 1;
    vx = roll_speed * static_cast<float>(direction);
    state = State::OnGirder;
    current_platform = platform;
    vy = 0.f;
}

void Barrel::update(float dt, Stage &stage) {
    switch (state) {
        case State::OnGirder:
            position.x += vx * dt;
            roll_distance += vx * dt * constants::BARREL_PLATFORM_ROLL_DISTANCE_FACTOR;
            if (current_platform && current_platform->covers_x(position.x, constants::BARREL_RADIUS, constants::BARREL_RADIUS)) {
                // stay glued to the surface: height follows the slope (tan angle)
                position.y = current_platform->surface_y_at(position.x);

                if (current_climbable) {
                    if (roll_down_climbable && ((vx < 0 && position.x < current_climbable->get_x_pos()) ||
                                                (vx > 0 && position.x > current_climbable->get_x_pos()))) {
                        vx = 0;
                        position.x = current_climbable->get_x_pos();
                        position.y = current_climbable->get_upper_y_pos();
                        state = State::RollingDownClimbable;
                        roll_distance = 0.f;
                    } else if ((vx < 0 && position.x < current_climbable->get_x_pos() - constants::BARREL_RADIUS) ||
                               (vx > 0 && position.x > current_climbable->get_x_pos() + constants::BARREL_RADIUS)) {
                        current_climbable.reset();
                    }
                } else {
                    current_climbable =
                        stage.get_climbables().find_climbable_down_at(position, constants::BARREL_RADIUS, constants::BARREL_RADIUS);
                    if (current_climbable) {
                        const float player_vertical_distance = stage.get_player()->get_position().y - position.y;
                        const float descent_chance =
                            std::clamp(constants::BARREL_LADDER_DESCENT_BASE_CHANCE +
                                           player_vertical_distance / constants::BARREL_LADDER_DESCENT_DISTANCE_PER_PERCENT,
                                       constants::BARREL_LADDER_DESCENT_BASE_CHANCE, constants::BARREL_LADDER_DESCENT_MAX_CHANCE);
                        roll_down_climbable = mod(stage.random_int(), constants::BARREL_LADDER_DESCENT_CHANCE_STEPS) < descent_chance;
                    }
                }
            } else {
                const std::shared_ptr<Platform> platform_below = stage.get_platforms().find_platform_underneath(
                    position, constants::BARREL_RADIUS, constants::BARREL_RADIUS, constants::SEAM_SNAP_DISTANCE);
                if (platform_below) {
                    set_on_platform(platform_below, stage.get_barrel_roll_speed(), std::signbit(vx) ? -1 : 1);
                    current_climbable.reset();
                    position.y = current_platform->surface_y_at(position.x);
                } else {
                    state = State::Falling;
                    current_climbable.reset();
                    vy = 0.f;
                }
            }
            break;
        case State::Falling:
            vy += constants::GRAVITY * dt;
            check_platform_intersection(stage.get_platforms(), dt, stage.get_barrel_roll_speed());
            position.x += vx * dt;
            position.y += vy * dt;

            if (state == State::Falling) {
                if (auto left_boundary = stage.get_left_boundary()) {
                    if (position.x < *left_boundary && !stage.is_barrel_boundary_gap(position)) {
                        position.x = *left_boundary;
                        vx = -vx;
                    }
                }
                if (auto right_boundary = stage.get_right_boundary()) {
                    if (position.x > *right_boundary && !stage.is_barrel_boundary_gap(position)) {
                        position.x = *right_boundary;
                        vx = -vx;
                    }
                }
            }
            break;
        case State::RollingDownClimbable:
            vy = stage.get_barrel_roll_speed();
            if (position.y < current_climbable->get_lower_y_pos()) {
                position.y += vy * dt;
                roll_distance += vy * dt * constants::BARREL_CLIMBABLE_ROLL_DISTANCE_FACTOR;
            } else {
                set_on_platform(current_climbable->get_lower_end(), stage.get_barrel_roll_speed());
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

void Barrel::accept(EntityVisitor &visitor) { visitor.visit(*this); }

std::unique_ptr<Component<Updatable>> Barrel::create_updatable_component() {
    return std::make_unique<Component<Updatable>>(std::static_pointer_cast<Barrel>(shared_from_this()));
}

std::unique_ptr<Component<Enemy>> Barrel::create_enemy_component() {
    return std::make_unique<Component<Enemy>>(std::static_pointer_cast<Barrel>(shared_from_this()));
}

std::unique_ptr<Component<Jumpable>> Barrel::create_jumpable_component() {
    return std::make_unique<Component<Jumpable>>(std::static_pointer_cast<Barrel>(shared_from_this()));
}

bool Barrel::touches(const sf::RectangleShape &player_shape) const {
    return shape.getGlobalBounds().findIntersection(player_shape.getGlobalBounds()).has_value();
}

void Barrel::on_hammer_hit(Stage &stage) {
    stage.add_to_score(position, constants::HAMMER_BARREL_SCORE);
    stage.get_player_data().increment_hammer_use_count();
    destroy();
}

void Barrel::check_platform_intersection(PlatformComponentRepository &platforms, float dt, float roll_speed) {
    set_on_platform(platforms.find_platform_underneath({position.x, position.y}, constants::BARREL_RADIUS, constants::BARREL_RADIUS,
                                                       platform_snap_distance(dt)),
                    roll_speed);
}

void Barrel::check_referenced_entities() {
    handle_destroyed_indirect(current_platform);
    if (handle_destroyed_indirect(current_climbable) && state == State::RollingDownClimbable) {
        state = State::Falling;
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

void Barrel::check_jumps_over(const Player &player, Stage &stage) {
    if (!player.has_jumped() || !stage.is_running()) {
        tracking_player_jump = false;
        crossed_above_barrel = false;
        scored_for_player_jump = false;
        player_jump_start_side = 0;
        return;
    }

    const sf::Vector2f player_position = player.get_position();
    const float player_x_difference = player_position.x - position.x;
    const float player_y_difference = (position.y - 2 * constants::BARREL_RADIUS) - player_position.y;
    const float horizontal_clearance = constants::BARREL_RADIUS + constants::PLAYER_WIDTH / 2.f;

    if (!tracking_player_jump) {
        tracking_player_jump = true;
        previous_player_x_difference = player_x_difference;
        previous_player_y_difference = player_y_difference;
        if (player_x_difference < -horizontal_clearance) {
            player_jump_start_side = -1;
        } else if (player_x_difference > horizontal_clearance) {
            player_jump_start_side = 1;
        }
        return;
    }

    const bool crossed_barrel = (previous_player_x_difference < 0.f && player_x_difference >= 0.f) ||
                                (previous_player_x_difference > 0.f && player_x_difference <= 0.f);
    if (!crossed_above_barrel && player_jump_start_side != 0 && crossed_barrel) {
        const float crossing_progress = previous_player_x_difference / (previous_player_x_difference - player_x_difference);
        const float crossing_y_difference =
            previous_player_y_difference + (player_y_difference - previous_player_y_difference) * crossing_progress;
        crossed_above_barrel = 0.f < crossing_y_difference && crossing_y_difference < constants::BARREL_JUMP_MAX_Y_DIFF;
    }

    previous_player_x_difference = player_x_difference;
    previous_player_y_difference = player_y_difference;

    const bool cleared_opposite_side = (player_jump_start_side < 0 && player_x_difference > horizontal_clearance) ||
                                       (player_jump_start_side > 0 && player_x_difference < -horizontal_clearance);
    if (crossed_above_barrel && cleared_opposite_side && !scored_for_player_jump) {
        scored_for_player_jump = true;
        stage.add_to_score(position - sf::Vector2f(constants::BARREL_RADIUS, 0), constants::BARREL_JUMP_SCORE);
        stage.get_player_data().increment_jumped_over_barrels_count();
    }
}
