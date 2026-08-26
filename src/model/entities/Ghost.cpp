#include "DK/model/entities/Ghost.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "DK/Constants.hpp"
#include "DK/model/PlayerData.hpp"
#include "DK/model/Stage.hpp"
#include "DK/model/components/Climbable.hpp"
#include "DK/model/components/Platform.hpp"
#include "DK/model/util/EntityVisitor.hpp"
#include "DK/util/Math.hpp"

Ghost::Ghost(Ref ref, std::shared_ptr<Platform> platform, float x_pos)
    : BaseEntity(ref), position({x_pos, platform->surface_y_at(x_pos)}), current_platform(platform) {}

void Ghost::update(float dt, Stage &stage) {
    switch (state) {
        case State::IdleOnPlatform:
            remaining_time -= dt;
            if (remaining_time <= 0.f) {
                // Start moving on platform
                state = State::MovingOnPlatform;
                moving_right = mod(stage.random_int(), 2) == 0; // Randomly choose direction
                remaining_time = constants::GHOST_MINIMUM_MOVING_DURATION +
                                 mod(stage.random_int(), constants::GHOST_MOVING_DURATION_STEPS) *
                                     (constants::GHOST_MAXIMUM_MOVING_DURATION - constants::GHOST_MINIMUM_MOVING_DURATION) /
                                     constants::GHOST_MOVING_DURATION_STEPS;
            }
            break;
        case State::MovingOnPlatform:
            {
                remaining_time -= dt;
                if (remaining_time <= 0.f) {
                    state = State::IdleOnPlatform;
                    remaining_time = constants::GHOST_MINIMUM_IDLE_DURATION +
                                     mod(stage.random_int(), constants::GHOST_IDLE_DURATION_STEPS) *
                                         (constants::GHOST_MAXIMUM_IDLE_DURATION - constants::GHOST_MINIMUM_IDLE_DURATION) /
                                         constants::GHOST_IDLE_DURATION_STEPS;
                    break;
                }

                float next_x = position.x + get_horizontal_speed() * dt;
                if (!current_platform->covers_x(next_x, constants::GHOST_WIDTH / 8.f, constants::GHOST_WIDTH / 8.f)) {
                    if (auto next_platform =
                            stage.get_platforms().find_platform_underneath({next_x, position.y}, constants::GHOST_WIDTH / 8.f,
                                                                           constants::GHOST_WIDTH / 8.f, constants::SEAM_SNAP_DISTANCE)) {
                        current_platform = next_platform;
                        position.y = current_platform->surface_y_at(position.x);
                    } else {
                        moving_right = !moving_right; // Change direction if the ghost reaches the edge of the platform
                    }
                }
                position.x += get_horizontal_speed() * dt;
                position.y = current_platform->surface_y_at(position.x);

                if (current_climbable) {
                    if (will_climb && ((!moving_right && position.x < current_climbable->get_x_pos()) ||
                                       (moving_right && position.x > current_climbable->get_x_pos()))) {
                        position.x = current_climbable->get_x_pos();
                        position.y = climbing_up ? current_climbable->get_lower_y_pos() : current_climbable->get_upper_y_pos();
                        state = State::Climbing;
                    } else if ((climbing_up &&
                                !current_climbable->can_climb_up(position, constants::GHOST_WIDTH / 2.f, constants::GHOST_HEIGHT / 2.f)) ||
                               (!climbing_up && !current_climbable->can_climb_down(position, constants::GHOST_WIDTH / 2.f,
                                                                                   constants::GHOST_HEIGHT / 2.f))) {
                        current_climbable.reset();
                    }
                } else {
                    current_climbable =
                        stage.get_climbables().find_climbable_down_at(position, constants::GHOST_WIDTH / 2.f, constants::GHOST_WIDTH / 2.f);
                    climbing_up = false;
                    if (!current_climbable) {
                        current_climbable = stage.get_climbables().find_climbable_up_at(position, constants::GHOST_WIDTH / 2.f,
                                                                                        constants::GHOST_WIDTH / 2.f);
                        climbing_up = true;
                    }
                    if (current_climbable) {
                        if (just_climbed) {
                            just_climbed = false;
                            will_climb = false; // Prevent immediate climbing after just climbing
                        } else {
                            will_climb = mod(stage.random_int(), 3) == 0; // Randomly decide whether the ghost will climb
                        }
                    }
                }
                break;
            }
        case State::Climbing:
            position.y += climbing_up ? -constants::GHOST_MOVING_SPEED * dt : constants::GHOST_MOVING_SPEED * dt;
            if ((climbing_up && position.y <= current_climbable->get_upper_y_pos()) ||
                (!climbing_up && position.y >= current_climbable->get_lower_y_pos())) {
                if (climbing_up) {
                    position.y = current_climbable->get_upper_y_pos();
                    current_platform = current_climbable->get_upper_end();
                } else {
                    position.y = current_climbable->get_lower_y_pos();
                    current_platform = current_climbable->get_lower_end();
                }
                state = State::MovingOnPlatform;
                current_climbable.reset();
                just_climbed = true;
            }
            break;
    }
}

bool Ghost::touches(const sf::RectangleShape &player_shape) const {
    sf::RectangleShape ghost_shape;
    ghost_shape.setSize(sf::Vector2f(constants::GHOST_WIDTH / 2.f, constants::GHOST_HEIGHT * 0.75f));
    sf::FloatRect ghost_bounds = ghost_shape.getLocalBounds();
    ghost_shape.setOrigin({ghost_bounds.size.x / 2.f, ghost_bounds.size.y});
    ghost_shape.setPosition(position - sf::Vector2f{0.f, constants::GHOST_LIFT}); // Adjust for ghost lift
    return ghost_shape.getGlobalBounds().findIntersection(player_shape.getGlobalBounds()).has_value();
}

void Ghost::accept(EntityVisitor &visitor) { visitor.visit(*this); }

void Ghost::check_referenced_entities() {
    if ((current_platform && current_platform->get_entity().is_destroyed()) ||
        (current_climbable && current_climbable->get_entity().is_destroyed())) {
        destroy();
    }
}

std::unique_ptr<Component<Updatable>> Ghost::create_updatable_component() {
    return std::make_unique<Component<Updatable>>(std::static_pointer_cast<Ghost>(shared_from_this()));
}

std::unique_ptr<Component<Enemy>> Ghost::create_enemy_component() {
    return std::make_unique<Component<Enemy>>(std::static_pointer_cast<Ghost>(shared_from_this()));
}

float Ghost::get_horizontal_speed() const {
    switch (state) {
        case State::MovingOnPlatform:
            return moving_right ? constants::GHOST_MOVING_SPEED : -constants::GHOST_MOVING_SPEED;
        default:
            return 0.f;
    }
}

void Ghost::on_hammer_hit(Stage &stage) {
    stage.add_to_score(position, constants::HAMMER_GHOST_SCORE);
    stage.get_player_data().increment_hammer_use_count();
    destroy();
}
