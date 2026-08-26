#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "DK/model/Declarations.hpp"
#include "DK/model/components/Updatable.hpp"
#include "DK/model/util/BaseEntity.hpp"

/**
 * @brief Player-controlled entity.
 *
 * The player can walk on platforms, jump, climb, and temporarily yield control
 * to a stage animation.
 */
class Player : public BaseEntity, public Updatable {
public:
    /**
     * @brief High-level player states used by the movement logic.
     */
    enum class State {
        OnPlatform,
        InAir,
        Climbing,
        Animated,
    };

    /**
     * @brief Requested horizontal movement direction.
     */
    enum class HorizontalDirection {
        Left,
        Right,
        None,
    };

    /**
     * @brief Requested vertical movement direction.
     */
    enum class VerticalDirection {
        Up,
        Down,
        None,
    };

    /**
     * @brief Creates a player entity in the repository.
     * @param ref Repository reference assigned to the player.
     */
    Player(Ref ref);

    void update(float dt, Stage &stage) override;

    /**
     * @brief Sets the horizontal direction currently requested by input.
     * @param dir Desired movement direction.
     */
    void set_horizontal_direction(HorizontalDirection dir);

    /**
     * @brief Sets the vertical direction currently requested by input.
     * @param dir Desired climbing direction.
     */
    void set_vertical_direction(VerticalDirection dir);

    /**
     * @brief Initiates a jump while the player is standing on a platform.
     */
    void jump();

    void check_referenced_entities() override;

    void accept(EntityVisitor &visitor) override;

    BaseEntity &get_entity() override { return *this; }

    std::unique_ptr<Component<Updatable>> create_updatable_component() override;

    sf::Vector2f get_position() const { return position; }

    bool is_facing_right() const { return facing_right; }
    void set_facing_right(bool facing_right) { this->facing_right = facing_right; }

    std::shared_ptr<Platform> get_current_platform() const { return current_platform; }

    float get_walking_time() const { return walking_time; }

    float get_climbing_time() const { return climbing_time; }

    bool has_jumped() const { return has_jumped_flag; }

    bool has_hammer() const { return hammer_time_remaining > 0.f; }

    float get_hammer_time_remaining() const { return hammer_time_remaining; }

    void enter_platform(std::shared_ptr<Platform> platform);

    void enter_platform(std::shared_ptr<Platform> platform, float x_pos);

    State get_state() const { return state; }

    /**
     * @brief Suspends player movement while an animation controls the entity.
     * @param animation Animation that takes control of the player.
     */
    void start_animation(AbstractAnimation *animation);

    /** @brief Releases animation control and returns the player to the air. */
    void stop_animation();

    AbstractAnimation *get_current_animation() const { return current_animation; }

    bool is_secondary_entity() const override { return false; }

private:
    State state;
    std::shared_ptr<Platform> current_platform;
    std::shared_ptr<Climbable> current_ladder;
    std::shared_ptr<Platform> last_fall_through_platform;
    bool facing_right = true;

    sf::Vector2f position;
    sf::Vector2f velocity;
    HorizontalDirection horizontal_direction = HorizontalDirection::None;
    VerticalDirection vertical_direction = VerticalDirection::None;
    float walking_time = 0.0f;
    float climbing_time = 0.0f;
    float hammer_time_remaining;
    bool has_jumped_flag = false;
    float y_before_jump = 0.0f;

    AbstractAnimation *current_animation = nullptr;

    sf::RectangleShape shape;

    float platform_snap_distance(float dt) const;

    bool handle_platform_fall_through();

    void die(Stage &stage);
};

#endif
