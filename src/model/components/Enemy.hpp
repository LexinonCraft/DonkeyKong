#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../util/EntityFromComponentAux.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

/**
 * @brief Behaviour interface for vertical structures that a player can climb.
 *
 * A climbable object connects the lower and upper platform endpoints at a fixed
 * x-position, allowing the player to move vertically between them.
 */
class Enemy : public EntityFromComponentAux {
public:
    virtual ~Enemy() {}

    virtual bool touches(const sf::RectangleShape &player_shape) const = 0;
    virtual void on_hammer_hit() = 0;
};

#endif
