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

    Player();

    /// advance the physics by `dt` seconds, given the stage's girders and ladders
    void update(float dt, const std::vector<Girder>& girders, const std::vector<Ladder>& ladders);

    /// set the direction the player is trying to move horizontally (left/right/none)
    void set_horizontal_direction(HorizontalDirection dir);
    /// set the direction the player is trying to move vertically (up/down/none)
    void set_vertical_direction(VerticalDirection dir);

    /// initialize a jump if the player is currently on a girder
    void jump();

    const sf::RectangleShape& get_shape() const;

private:
    // check if there is a girder below the player and return a pointer to it, or nullptr if there is none
    const Girder *find_girder_below(const std::vector<Girder>& girders) const;
    // check if there is a ladder leading up from the player's current position and return a pointer to it, or nullptr if there is none
    const Ladder *find_ladder_leading_up(const std::vector<Ladder>& ladders) const;
    // check if there is a ladder leading down from the player's current position and return a pointer to it, or nullptr if there is none
    const Ladder *find_ladder_leading_down(const std::vector<Ladder>& ladders) const;

    State state;
    const Girder* current_girder = nullptr;
    const Ladder* current_ladder = nullptr;

    sf::Vector2f position;
    sf::Vector2f velocity;
    HorizontalDirection horizontal_direction = HorizontalDirection::None;
    VerticalDirection vertical_direction = VerticalDirection::None;

    sf::RectangleShape shape;
};

#endif