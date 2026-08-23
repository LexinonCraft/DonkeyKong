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

    /**
     * @brief Returns the slope of the girder surface at a given x position.
     * @param x Horizontal position.
     * @returns dy/dx value for the surface at x.
     */
    float slope_at(float x) const override;

    /**
     * @brief Returns the y-coordinate of the girder surface at a given x position.
     * @param x Horizontal position.
     * @returns Surface height.
     */
    float surface_y_at(float x) const override;

    /**
     * @brief Returns whether the girder covers the supplied x-coordinate.
     * @param x Horizontal position.
     * @returns True if x lies within the girder's horizontal span.
     */
    bool covers_x(float x, float h_tolerance_left, float h_tolerance_right) const override;

    /**
     * @brief Returns the direction in which a barrel should roll on this girder.
     * @returns +1 toward the right, -1 toward the left, 0 for a flat surface.
     */
    int downhill_sign() const override;

    /**
     * @brief Returns the higher end of the girder.
     * @returns World-space endpoint with smaller y value.
     */
    sf::Vector2f high_end() const override;

    /**
     * @brief Returns whether the girder is currently usable as a standing surface.
     * @returns Always true for a static girder.
     */
    bool is_active() const override;

    /**
     * @brief Returns the displacement of an object lying on this girder.
     * @param x Horizontal position.
     * @param dt Time step.
     * @returns Zero displacement for a static surface.
     */
    sf::Vector2f displacement_at(float x, float dt) const override;

    /**
     * @brief Dispatches the girder to the entity visitor.
     * @param visitor Visitor used for type-based rendering logic.
     */
    void accept(EntityVisitor &visitor) override;

    /**
     * @brief Returns the underlying entity as an abstract base pointer.
     * @returns Reference to this entity.
     */
    BaseEntity &get_entity() override { return *this; }

    float get_width() const { return right.x - left.x; }

    sf::Vector2f get_left() const { return left; }

    sf::Vector2f get_right() const { return right; }

    void set_left(sf::Vector2f new_left) { left = new_left; }

    void set_right(sf::Vector2f new_right) { right = new_right; }

    Color get_color() const { return color; }

    /**
     * @brief Creates the platform component for this girder.
     * @returns Unique pointer to the platform component wrapper.
     */
    std::unique_ptr<Component<Platform>> create_platform_component() override;

    bool is_secondary_entity() const override { return false; }

private:
    sf::Vector2f left;
    sf::Vector2f right;
    Color color;
};

#endif
