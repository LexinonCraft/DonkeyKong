#ifndef PICKABLE_HPP
#define PICKABLE_HPP

#include <SFML/Graphics/RectangleShape.hpp>

#include "DK/model/util/EntityFromComponentAux.hpp"

/**
 * @brief Behaviour interface for entities that the player can pick up.
 */
class Pickable : public EntityFromComponentAux {
public:
    enum class Type { Hammer };

    ~Pickable() override = default;

    /**
     * @brief Returns the effect type provided by this pickable.
     *
     * Called after the player touches the pickable to determine which effect
     * to apply.
     *
     * @returns Type of the pickable effect.
     */
    virtual Type get_type() const = 0;

    /**
     * @brief Returns whether this pickable intersects the player.
     *
     * Called during player updates while the player is on a platform or in the
     * air to find a pickable that can be collected.
     *
     * @param player_shape Collision shape of the player.
     * @returns True if the pickable touches the player.
     */
    virtual bool touches(const sf::RectangleShape &player_shape) const = 0;

    /**
     * @brief Applies the entity-specific response to being collected.
     *
     * Called after the player has received the pickable's effect.
     */
    virtual void on_picked_up() = 0;
};

#endif
