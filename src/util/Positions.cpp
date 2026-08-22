#include <stdexcept>

#include "DK/util/Positions.hpp"
#include "DK/Constants.hpp"

sf::Vector2f get_absolute_position(const sf::Vector2f &relative_position, AnchorPosition anchor) {
    switch (anchor) {
        case AnchorPosition::TopLeft:
            return {relative_position.x, relative_position.y - constants::VIEW_HEIGHT};
        case AnchorPosition::TopCenter:
            return {relative_position.x + constants::VIEW_WIDTH / 2.f, relative_position.y - constants::VIEW_HEIGHT};
        case AnchorPosition::TopRight:
            return {relative_position.x + constants::VIEW_WIDTH, relative_position.y - constants::VIEW_HEIGHT};
        case AnchorPosition::CenterLeft:
            return {relative_position.x, relative_position.y - constants::VIEW_HEIGHT / 2.f};
        case AnchorPosition::Center:
            return {relative_position.x + constants::VIEW_WIDTH / 2.f, relative_position.y - constants::VIEW_HEIGHT / 2.f};
        case AnchorPosition::CenterRight:
            return {relative_position.x + constants::VIEW_WIDTH, relative_position.y - constants::VIEW_HEIGHT / 2.f};
        case AnchorPosition::BottomLeft:
            return {relative_position.x, relative_position.y};
        case AnchorPosition::BottomCenter:
            return {relative_position.x + constants::VIEW_WIDTH / 2.f, relative_position.y};
        case AnchorPosition::BottomRight:
            return {relative_position.x + constants::VIEW_WIDTH, relative_position.y};
        default:
            throw std::logic_error("Unknown anchor position");
    }
}
