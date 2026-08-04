#ifndef LADDER_H
#define LADDER_H

#include "Girder.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

/// @brief Represents a ladder connecting two girders at a specific x position.
class Ladder {
public:
    Ladder(const Girder* lower_end, const Girder* upper_end, float x_pos);

    const Girder* get_lower_end() const;
    const Girder* get_upper_end() const;
    float get_x_pos() const;
    float get_lower_y_pos() const;
    float get_upper_y_pos() const;
    const sf::RectangleShape& get_shape() const;

private:
    const Girder* lower_end;
    const Girder* upper_end;
    const float x_pos;
    sf::RectangleShape shape;
};
#endif
