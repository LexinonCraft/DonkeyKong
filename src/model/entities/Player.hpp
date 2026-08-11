#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "../Declarations.hpp"
#include "../components/Climbable.hpp"
#include "../util/BaseEntity.hpp"
#include "../components/Updatable.hpp"

/// A player character that can move left/right on girders, jump, and climb ladders.
class Player : public BaseEntity, public Updatable {
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

    Player(Ref ref);

    /// advance the physics by `dt` seconds, given the stage's girders and ladders
    void update(float dt, Level &level) override;

    /// set the direction the player is trying to move horizontally (left/right/none)
    void set_horizontal_direction(HorizontalDirection dir);
    /// set the direction the player is trying to move vertically (up/down/none)
    void set_vertical_direction(VerticalDirection dir);

    /// initialize a jump if the player is currently on a girder
    void jump();

    const sf::RectangleShape &get_shape() const;

    void accept(EntityVisitor &visitor) override;

private:
    State state;
    std::weak_ptr<Platform> current_platform;
    std::weak_ptr<Climbable> current_ladder;

    sf::Vector2f position;
    sf::Vector2f velocity;
    HorizontalDirection horizontal_direction = HorizontalDirection::None;
    VerticalDirection vertical_direction = VerticalDirection::None;

    sf::RectangleShape shape;
};

#endif
