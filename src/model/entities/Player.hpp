#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "../Declarations.hpp"
#include "../components/Climbable.hpp"
#include "../util/BaseEntity.hpp"
#include "../components/Updatable.hpp"

/**
 * @brief Player-controlled entity.
 *
 * The player can walk on girders, jump into the air, and climb ladders using a
 * small state machine composed of OnPlatform, InAir and Climbing states.
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
        Dying,
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

    /**
     * @brief Advances the player by one physics update step.
     * @param dt Time step in seconds.
     * @param stage Stage used for collision and climbable lookup.
     */
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

    /**
     * @brief Returns the SFML shape used for rendering.
     * @return Player geometry.
     */
    const sf::RectangleShape &get_shape() const;

    /**
     * @brief Clears references to deleted platforms or ladders.
     */
    void check_referenced_entities() override;

    /**
     * @brief Dispatches this entity to the visitor.
     * @param visitor Visitor used for type-based rendering/factory logic.
     */
    void accept(EntityVisitor &visitor) override;

    /**
     * @brief Returns the underlying entity as an abstract base pointer.
     * @return Reference to this entity.
     */
    BaseEntity &get_entity() override { return *this; }

    /**
     * @brief Creates the updatable component for this player.
     * @return Unique pointer to the component wrapper.
     */
    std::unique_ptr<Component<Updatable>> create_updatable_component() override {
        return std::make_unique<Component<Updatable>>(std::static_pointer_cast<Player>(shared_from_this()));
    }

    sf::Vector2f get_position() const { return position; }

    bool is_facing_right() const { return facing_right; }

private:
    State state;
    std::shared_ptr<Platform> current_platform;
    std::shared_ptr<Climbable> current_ladder;
    bool facing_right = true;

    sf::Vector2f position;
    sf::Vector2f velocity;
    HorizontalDirection horizontal_direction = HorizontalDirection::None;
    VerticalDirection vertical_direction = VerticalDirection::None;

    sf::RectangleShape shape;
};

#endif
