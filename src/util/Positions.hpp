#ifndef POSITIONS_HPP
#define POSITIONS_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

/**
 * @brief Enum class representing anchor positions for positioning and transformations.
 */
enum class AnchorPosition { TopLeft, TopCenter, TopRight, CenterLeft, Center, CenterRight, BottomLeft, BottomCenter, BottomRight };

/**
 * @brief Get the corresponding position in a square with side length 1 for a given anchor position.
 *
 * @param anchor The anchor position.
 * @return The corresponding position.
 */
sf::Vector2f get_position_in_normalized_coordinates(AnchorPosition anchor);

/**
 * @brief Convert a position relative to an anchor of the screen to an absolute position on the screen.
 *
 * @param relative_position The position relative to the anchor.
 * @param anchor The anchor position.
 * @return The absolute position on the screen.
 */
sf::Vector2f get_absolute_position(const sf::Vector2f &relative_position, AnchorPosition anchor);

/**
 * @brief Compute the corresponding position on target for a given anchor position.
 *
 * @tparam T type extending sf::Transformable and having getLocalBounds() method
 * @param target The target object.
 * @param anchor The anchor position.
 * @return The corresponding position on the target.
 */
template <typename T> sf::Vector2f compute_origin_for_anchor(T &target, AnchorPosition anchor) {
    sf::FloatRect bounds = target.getLocalBounds();
    auto normalized_position = get_position_in_normalized_coordinates(anchor);
    return {bounds.size.x * normalized_position.x, bounds.size.y * normalized_position.y};
}

/**
 * @brief Set the origin of the target to the corresponding position for a given anchor position.
 *
 * @tparam T type extending sf::Transformable and having getLocalBounds() method
 * @param target The target object.
 * @param anchor The anchor position.
 */
template <typename T> void set_origin(T &target, AnchorPosition anchor) { target.setOrigin(compute_origin_for_anchor(target, anchor)); }

/**
 * @brief Set the target object to the specified size.
 *
 * @tparam T type extending sf::Transformable and having getLocalBounds() method
 * @param target The target object.
 * @param size The desired size.
 */
template <typename T> void set_to_size(T &target, const sf::Vector2f &size) {
    sf::FloatRect bounds = target.getLocalBounds();
    target.setScale({size.x / bounds.size.x, size.y / bounds.size.y});
}

/**
 * @brief Potentially flip the target object horizontally.
 *
 * @param transformable The target object.
 * @param flip Whether to flip the object horizontally.
 */
void flip_horizontally(sf::Transformable &transformable, bool flip);

/**
 * @brief Scale the target object by a given factor, considering the current scale.
 *
 * @param transformable The target object.
 * @param scale The scale factor.
 */
void scale(sf::Transformable &transformable, float scale);

/**
 * @brief Potentially rotate the target object by 180 degrees around the specified anchor position if requested (independent of the set
 * origin).
 *
 * @tparam T type extending sf::Transformable and having getLocalBounds() method
 * @param target The target object.
 * @param anchor The anchor position.
 * @param rotate Whether to perform the rotation.
 */
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
