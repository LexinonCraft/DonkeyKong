#ifndef PICKABLE_HPP
#define PICKABLE_HPP

#include <SFML/Graphics/RectangleShape.hpp>

#include "../util/EntityFromComponentAux.hpp"

class Pickable : public EntityFromComponentAux {
public:
    enum class Type { Hammer };

    virtual ~Pickable() {}

    virtual Type get_type() const = 0;
    virtual bool touches(const sf::RectangleShape &player_shape) const = 0;
    virtual void on_picked_up() = 0;
};

#endif
