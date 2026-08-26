#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "DK/model/util/EntityFromComponentAux.hpp"

/**
 * @brief Behaviour interface for entities that can collide with and be hit by the player.
 */
class Enemy : public EntityFromComponentAux {
public:
    ~Enemy() override = default;

    virtual bool touches(const sf::RectangleShape &player_shape) const = 0;
    virtual sf::Vector2f get_position() const = 0;
    virtual void on_hammer_hit(Stage &stage) = 0;
};

#endif
