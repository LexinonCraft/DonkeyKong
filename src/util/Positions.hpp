#ifndef POSITIONS_HPP
#define POSITIONS_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

enum class AnchorPosition { TopLeft, TopCenter, TopRight, CenterLeft, Center, CenterRight, BottomLeft, BottomCenter, BottomRight };

sf::Vector2f get_position_in_normalized_coordinates(AnchorPosition anchor);

sf::Vector2f get_absolute_position(const sf::Vector2f &relative_position, AnchorPosition anchor);

template <typename T> sf::Vector2f compute_origin_for_anchor(T &target, AnchorPosition anchor) {
    sf::FloatRect bounds = target.getLocalBounds();
    auto normalized_position = get_position_in_normalized_coordinates(anchor);
    return {bounds.size.x * normalized_position.x, bounds.size.y * normalized_position.y};
}

template <typename T> void set_origin(T &target, AnchorPosition anchor) { target.setOrigin(compute_origin_for_anchor(target, anchor)); }

template <typename T> void set_to_size(T &target, const sf::Vector2f &size) {
    sf::FloatRect bounds = target.getLocalBounds();
    target.setScale({size.x / bounds.size.x, size.y / bounds.size.y});
}

void flip_horizontally(sf::Transformable &transformable, bool flip);

void scale(sf::Transformable &transformable, float scale);

template <typename T> void rotate_180_degrees(T &target, AnchorPosition anchor, bool rotate) {
    if (!rotate) {
        return;
    }

    auto origin_diff = compute_origin_for_anchor(target, anchor) - target.getOrigin();
    auto scale = target.getScale();

    target.setRotation(sf::degrees(180.f));
    target.setPosition(target.getPosition() + sf::Vector2f(origin_diff.x * scale.x, origin_diff.y * scale.y) * 2.f);
}

#endif
