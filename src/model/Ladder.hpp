#ifndef LADDER_H
#define LADDER_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>

#include "Platform.hpp"
#include "../util/RepositoryElement.hpp"

/// @brief Represents a ladder connecting two girders at a specific x position.
class Ladder : public RepositoryElement<Ladder> {
public:
    Ladder(Ref<Ladder> ref, std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_pos);

    std::shared_ptr<Platform> get_lower_end() const;
    std::shared_ptr<Platform> get_upper_end() const;
    float get_x_pos() const;
    float get_lower_y_pos() const;
    float get_upper_y_pos() const;
    const sf::RectangleShape& get_shape() const;

private:
    std::shared_ptr<Platform> lower_end;
    std::shared_ptr<Platform> upper_end;
    const float x_pos;
    sf::RectangleShape shape;
};
#endif
