#ifndef BARREL_HPP
#define BARREL_HPP

#include <memory>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "DK/model/Declarations.hpp"
#include "DK/model/components/Enemy.hpp"
#include "DK/model/components/Jumpable.hpp"
#include "DK/model/components/Updatable.hpp"
#include "DK/model/util/BaseEntity.hpp"

/**
 * @brief Enemy barrel that rolls across platforms, descends climbables, and falls when unsupported.
 *
 * Its state tracks whether it is attached to a platform, falling, or rolling down
 * a climbable.
 */
class Barrel : public BaseEntity, public Updatable, public Enemy, public Jumpable {
public:
    /**
     * @brief Current barrel state.
     */
    enum class State { OnGirder, Falling, RollingDownClimbable };

    /**
     * @brief Creates a barrel at a world position.
     * @param ref Repository reference assigned to the barrel.
     * @param position Initial world position.
     */
    Barrel(Ref ref, sf::Vector2f position);

    /**
     * @brief Places the barrel on a platform and sets its rolling direction.
     * @param platform Platform surface to rest on.
     * @param roll_speed Horizontal rolling speed.
     * @param roll_direction Optional direction to roll: -1 for left, 1 for right, or 0 to use the platform's slope.
     */
    void set_on_platform(std::shared_ptr<Platform> platform, float roll_speed, int roll_direction = 0);

    void update(float dt, Stage &stage) override;

    State get_state() const { return state; }

    sf::Vector2f get_position() const override { return position; }

    float get_vx() const { return vx; }

    float get_vy() const { return vy; }

    void accept(EntityVisitor &visitor) override;

    void check_referenced_entities() override;

    BaseEntity &get_entity() override { return *this; }

    std::unique_ptr<Component<Updatable>> create_updatable_component() override;

    std::unique_ptr<Component<Enemy>> create_enemy_component() override;

    std::unique_ptr<Component<Jumpable>> create_jumpable_component() override;

    bool touches(const sf::RectangleShape &player_shape) const override;

    void on_hammer_hit(Stage &stage) override;

    float get_roll_distance() const { return roll_distance; }

    void check_jumps_over(const Player &player, Stage &stage) override;

private:
    sf::Vector2f position;
    float vx = 0.f;
    float vy = 0.f;

    State state = State::Falling;
    std::shared_ptr<Platform> current_platform = nullptr;
    std::shared_ptr<Climbable> current_climbable = nullptr;
    bool roll_down_climbable = false;
    float roll_distance = 0.f;
    bool tracking_player_jump = false;
    bool crossed_above_barrel = false;
    bool scored_for_player_jump = false;
    int player_jump_start_side = 0;
    float previous_player_x_difference = 0.f;
    float previous_player_y_difference = 0.f;

    sf::CircleShape shape;

    void check_platform_intersection(PlatformComponentRepository &platforms, float dt, float roll_speed);

    float platform_snap_distance(float dt) const;
};

#endif
