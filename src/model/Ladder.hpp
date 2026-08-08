#ifndef LADDER_H
#define LADDER_H

#include <SFML/Graphics/RectangleShape.hpp>

#include "Platform.hpp"
#include "../util/RepositoryElement.hpp"

/// @brief Represents a ladder connecting two girders at a specific x position.
class Ladder : public RepositoryElement<Ladder> {
public:
    Ladder(Ref<Ladder> ref, Ref<Platform> lower_end, Ref<Platform> upper_end, float x_pos);

    Ref<Platform> get_lower_end() const;
    Ref<Platform> get_upper_end() const;
    float get_x_pos() const;
    float get_lower_y_pos() const;
    float get_upper_y_pos() const;
    const sf::RectangleShape& get_shape() const;

private:
    Ref<Platform> lower_end;
    Ref<Platform> upper_end;
    const float x_pos;
    sf::RectangleShape shape;
};
#endif
