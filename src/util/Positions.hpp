#ifndef POSITIONS_HPP
#define POSITIONS_HPP

#include <SFML/System/Vector2.hpp>

enum class AnchorPosition {
    TopLeft,
    TopCenter,
    TopRight,
    CenterLeft,
    Center,
    CenterRight,
    BottomLeft,
    BottomCenter,
    BottomRight
};

sf::Vector2f get_absolute_position(const sf::Vector2f &relative_position, AnchorPosition anchor);

#endif
