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

    virtual Type get_type() const = 0;
    virtual bool touches(const sf::RectangleShape &player_shape) const = 0;
    virtual void on_picked_up() = 0;
};

#endif
