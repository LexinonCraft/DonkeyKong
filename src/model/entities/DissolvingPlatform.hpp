#ifndef DISSOLVING_PLATFORM_HPP
#define DISSOLVING_PLATFORM_HPP

#include <memory>

#include <SFML/System/Vector2.hpp>

#include "DK/model/Declarations.hpp"
#include "DK/model/components/Platform.hpp"
#include "DK/model/components/Updatable.hpp"
#include "DK/model/util/BaseEntity.hpp"

/**
 * @brief Dissolving platform entity that forms the walkable floors of the level.
 *
 * A dissolving platform is a static platform that can dissolve over time,
 * affecting the player's ability to traverse it. Its geometry defines the position
 * and width of the platform.
 */
class DissolvingPlatform : public BaseEntity, public Platform, public Updatable {
public:
    /**
     * @brief Creates a dissolving platform at the specified position with the given width.
     * @param ref Repository reference assigned to the platform.
     * @param position World-space position of the platform.
     * @param width Width of the platform.
     */
    DissolvingPlatform(Ref ref, sf::Vector2f position, float width);

    /**
     * @brief Returns the slope of the dissolving platform surface at a given x position.
     * @param x Horizontal position.
     * @returns dy/dx value for the surface at x.
     */
    float slope_at(float x) const override;

    /**
     * @brief Returns the y-coordinate of the dissolving platform surface at a given x position.
     * @param x Horizontal position.
     * @returns Surface height.
     */
    float surface_y_at(float x) const override;

    /**
     * @brief Returns whether the dissolving platform covers the supplied x-coordinate.
     * @param x Horizontal position.
     * @returns True if x lies within the platform's horizontal span.
     */
    bool covers_x(float x, float h_tolerance_left, float h_tolerance_right) const override;

    /**
     * @brief Returns the direction in which a barrel should roll on this dissolving platform.
     * @returns +1 toward the right, -1 toward the left, 0 for a flat surface.
     */
    int downhill_sign() const override;

    /**
     * @brief Returns the higher end of the dissolving platform.
     * @returns World-space endpoint with smaller y value.
     */
    sf::Vector2f high_end() const override;

    /**
     * @brief Returns whether the dissolving platform is currently usable as a standing surface.
     * @returns Always true for a static platform.
     */
    bool is_active() const override;

    /**
     * @brief Returns the displacement of an object lying on this dissolving platform.
     * @param x Horizontal position.
     * @param dt Time step.
     * @returns Zero displacement for a static surface.
     */
    sf::Vector2f displacement_at(float x, float dt) const override;

    /**
     * @brief Dispatches the dissolving platform to the entity visitor.
     * @param visitor Visitor used for type-based rendering logic.
     */
    void accept(EntityVisitor &visitor) override;

    /**
     * @brief Returns the underlying entity as an abstract base pointer.
     * @returns Reference to this entity.
     */
    BaseEntity &get_entity() override { return *this; }

    sf::Vector2f get_position() const { return position; }

    float get_width() const { return width; }

    void update(float dt, Stage &stage) override;

    /**
     * @brief Creates the platform component for this dissolving platform.
     * @returns Unique pointer to the platform component wrapper.
     */
    std::unique_ptr<Component<Platform>> create_platform_component() override;

    std::unique_ptr<Component<Updatable>> create_updatable_component() override;

    bool fall_through(std::shared_ptr<Player> player) override;

    bool has_dissolved() const;

private:
    sf::Vector2f position;
    float width;
    bool is_dissolving = false;
    bool dissolved = false;
    float dissolve_timer = 0.f;
};

#endif
