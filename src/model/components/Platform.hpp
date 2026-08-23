#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <memory>

#include <SFML/System/Vector2.hpp>

#include "DK/model/Declarations.hpp"
#include "DK/model/util/EntityFromComponentAux.hpp"

/**
 * @brief Behaviour interface for surfaces that entities can stand on.
 *
 * Platform-like objects are represented by an entity implementing this interface so that
 * barrels and the player can query the geometric properties of the surface they
 * are walking on.
 */
class Platform : public EntityFromComponentAux {
public:
    virtual ~Platform() = default;

    /**
     * @brief Returns whether the platform spans the given world x position.
     * @param x Horizontal world coordinate.
     * @returns True if x lies on the platform.
     */
    virtual bool covers_x(float x, float h_tolerance_left, float h_tolerance_right) const = 0;

    /**
     * @brief Returns the platform surface height at a given x position.
     * @param x Horizontal world coordinate.
     * @returns Y coordinate of the surface at x.
     */
    virtual float surface_y_at(float x) const = 0;

    /**
     * @brief Returns the slope of the platform surface at x.
     * @param x Horizontal world coordinate.
     * @returns dy/dx value of the surface.
     */
    virtual float slope_at(float x) const = 0;

    /**
     * @brief Returns whether the platform is currently usable.
     * @returns True if entities may stand on it.
     */
    virtual bool is_active() const = 0;

    /**
     * @brief Returns the displacement that an object on this platform experiences.
     * @param x Horizontal world coordinate.
     * @param dt Time step.
     * @returns Displacement vector for the given position and timestep.
     */
    virtual sf::Vector2f displacement_at(float x, float dt) const = 0;

    /**
     * @brief Returns the direction in which the surface slopes downward.
     * @returns -1 for a slope down to the left, +1 for down to the right, 0 for horizontal.
     */
    virtual int downhill_sign() const = 0;

    /**
     * @brief Returns the higher end of the platform.
     * @returns World-space endpoint with smaller y coordinate.
     */
    virtual sf::Vector2f high_end() const = 0;

    virtual bool fall_through(std::shared_ptr<Player> player) { return false; }
};

#endif
