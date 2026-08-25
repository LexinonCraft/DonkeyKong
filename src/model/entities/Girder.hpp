#ifndef GIRDER_HPP
#define GIRDER_HPP

#include <memory>

#include <SFML/System/Vector2.hpp>

#include "DK/model/Declarations.hpp"
#include "DK/model/components/Platform.hpp"
#include "DK/model/util/BaseEntity.hpp"

/**
 * @brief Sloped platform entity that forms the walkable floors of the level.
 *
 * A girder is a directed line segment with a surface that barrels and the player
 * can traverse. Its geometry defines the slope and the lower/upper endpoint used
 * for platform detection and player placement.
 */
class Girder : public BaseEntity, public Platform {
public:
    enum class Color {
        Red,
        Blue,
    };

    /**
     * @brief Creates a girder between its left and right endpoints.
     * @param ref Repository reference assigned to the girder.
     * @param left First endpoint of the line segment.
     * @param right Second endpoint of the line segment.
     */
    Girder(Ref ref, sf::Vector2f left, sf::Vector2f right);

    /**
     * @brief Creates a girder between its left and right endpoints.
     * @param ref Repository reference assigned to the girder.
     * @param left First endpoint of the line segment.
     * @param right Second endpoint of the line segment.
     * @param color Color of the girder for rendering purposes.
     */
    Girder(Ref ref, sf::Vector2f left, sf::Vector2f right, Color color);

    float slope_at(float x) const override;

    float surface_y_at(float x) const override;

    bool covers_x(float x, float h_tolerance_left, float h_tolerance_right) const override;

    int downhill_sign() const override;

    sf::Vector2f high_end() const override;

    bool is_active() const override;

    sf::Vector2f displacement_at(float x, float dt) const override;

    void accept(EntityVisitor &visitor) override;

    BaseEntity &get_entity() override { return *this; }

    float get_width() const { return right.x - left.x; }

    sf::Vector2f get_left() const { return left; }

    sf::Vector2f get_right() const { return right; }

    void set_left(sf::Vector2f new_left) { left = new_left; }

    void set_right(sf::Vector2f new_right) { right = new_right; }

    Color get_color() const { return color; }

    std::unique_ptr<Component<Platform>> create_platform_component() override;

    bool is_secondary_entity() const override { return false; }

private:
    sf::Vector2f left;
    sf::Vector2f right;
    Color color;
};

#endif
