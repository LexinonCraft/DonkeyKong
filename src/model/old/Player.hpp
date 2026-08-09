#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <optional>

#include "Declarations.hpp"
#include "Ladder.hpp"
#include "Entity.hpp"

/// A player character that can move left/right on girders, jump, and climb ladders.
class Player : public Entity {
public:
    enum class State {
        OnPlatform,
        InAir,
        Climbing,
    };
    enum class HorizontalDirection {
        Left,
        Right,
        None,
    };
    enum class VerticalDirection {
        Up,
        Down,
        None,
    };

    Player(Ref<Entity> ref);

    /// advance the physics by `dt` seconds, given the stage's girders and ladders
    void update(Level &level, float dt) override;

    /// set the direction the player is trying to move horizontally (left/right/none)
    void set_horizontal_direction(HorizontalDirection dir);
    /// set the direction the player is trying to move vertically (up/down/none)
    void set_vertical_direction(VerticalDirection dir);

    /// initialize a jump if the player is currently on a girder
    void jump();

    const sf::RectangleShape& get_shape() const;

    void accept(EntityVisitor &visitor) const override;

private:
    // check if there is a platform below the player and return a pointer to it, or nullptr if there is none
    const std::optional<Ref<Platform>> find_platform_below(const PlatformRepository &platforms) const;
    // check if there is a ladder leading up from the player's current position and return a pointer to it, or nullptr if there is none
    const std::optional<Ref<Ladder>> find_ladder_leading_up(const LadderRepository &ladders) const;
    // check if there is a ladder leading down from the player's current position and return a pointer to it, or nullptr if there is none
    const std::optional<Ref<Ladder>> find_ladder_leading_down(const LadderRepository &ladders) const;

    State state;
    std::optional<Ref<Platform>> current_platform = std::nullopt;
    std::optional<Ref<Ladder>> current_ladder = std::nullopt;

    sf::Vector2f position;
    sf::Vector2f velocity;
    HorizontalDirection horizontal_direction = HorizontalDirection::None;
    VerticalDirection vertical_direction = VerticalDirection::None;

    sf::RectangleShape shape;
};

#endif