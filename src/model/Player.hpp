#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "Girder.hpp"
#include "Ladder.hpp"

/// A player character that can move left/right on girders, jump, and climb ladders.
class Player {
public:
    enum class State {
        OnGirder,
        InAir,
        ClimbingUp,
        ClimbingDown,
    };
    enum class HorizontalDirection {
        Left,
        Right,
        None,
    };

    Player();

    /// advance the physics by `dt` seconds, given the stage's girders and ladders
    void update(float dt, const std::vector<Girder>& girders, const std::vector<Ladder>& ladders);

    /// set the direction the player is trying to move horizontally (left/right/none)
    void set_horizontal_direction(HorizontalDirection dir);

    /// initialize a jump if the player is currently on a girder
    void jump();

    /// start climbing up a ladder, if the player is currently on a girder and there is a ladder leading up at the player's x position
    void start_climbing_up();
    /// start climbing down a ladder, if the player is currently on a girder and there is a ladder leading down at the player's x position
    void start_climbing_down();

    const sf::RectangleShape& get_shape() const;

private:
    State state;
    const Girder* current_girder = nullptr;
    const Ladder* current_ladder = nullptr;

    sf::Vector2f position;
    sf::Vector2f velocity;
    HorizontalDirection horizontal_direction = HorizontalDirection::None;

    sf::RectangleShape shape;
};

#endif