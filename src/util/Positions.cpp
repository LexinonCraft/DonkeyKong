#include "DK/util/Positions.hpp"

#include <stdexcept>

#include "DK/Constants.hpp"

sf::Vector2f get_position_in_normalized_coordinates(AnchorPosition anchor) {
    switch (anchor) {
        case AnchorPosition::TopLeft:
            return {0.f, 0.f};
        case AnchorPosition::TopCenter:
            return {0.5f, 0.f};
        case AnchorPosition::TopRight:
            return {1.f, 0.f};
        case AnchorPosition::CenterLeft:
            return {0.f, 0.5f};
        case AnchorPosition::Center:
            return {0.5f, 0.5f};
        case AnchorPosition::CenterRight:
            return {1.f, 0.5f};
        case AnchorPosition::BottomLeft:
            return {0.f, 1.f};
        case AnchorPosition::BottomCenter:
            return {0.5f, 1.f};
        case AnchorPosition::BottomRight:
            return {1.f, 1.f};
        default:
            throw std::logic_error("Unknown anchor position");
    }
}

sf::Vector2f get_absolute_position(const sf::Vector2f &relative_position, AnchorPosition anchor) {
    auto normalized_position = get_position_in_normalized_coordinates(anchor);
    return sf::Vector2f(normalized_position.x * constants::VIEW_WIDTH, (normalized_position.y - 1.f) * constants::VIEW_HEIGHT) +
           relative_position;
}

void flip_horizontally(sf::Transformable &transformable, bool flip) {
    sf::Vector2f scale = transformable.getScale();
    transformable.setScale({flip ? -scale.x : scale.x, scale.y});
}

void scale(sf::Transformable &transformable, float scale) { transformable.setScale(transformable.getScale() * scale); }
