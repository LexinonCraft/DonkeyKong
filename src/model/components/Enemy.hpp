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

    /**
     * @brief Returns whether this enemy intersects the player.
     *
     * Called during player updates to find an enemy currently touching the
     * player.
     *
     * @param player_shape Collision shape of the player.
     * @returns True if the enemy touches the player.
     */
    virtual bool touches(const sf::RectangleShape &player_shape) const = 0;

    /**
     * @brief Returns the enemy's position in world space.
     *
     * Called after a collision is detected to determine whether the enemy is
     * in front of the hammer-wielding player.
     *
     * @returns World-space position of the enemy.
     */
    virtual sf::Vector2f get_position() const = 0;

    /**
     * @brief Applies the entity-specific response to a hammer hit.
     *
     * Called when the player touches the enemy while holding a hammer and the
     * enemy is in front of the player.
     *
     * @param stage Stage in which the hit response is applied.
     */
    virtual void on_hammer_hit(Stage &stage) = 0;
};

#endif
