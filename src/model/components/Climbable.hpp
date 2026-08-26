#ifndef CLIMBABLE_HPP
#define CLIMBABLE_HPP

#include <memory>

#include <SFML/System/Vector2.hpp>

#include "DK/model/components/Platform.hpp"
#include "DK/model/util/EntityFromComponentAux.hpp"

/**
 * @brief Behaviour interface for vertical structures that a player can climb.
 *
 * A climbable object connects the lower and upper platform endpoints at a fixed
 * x-position, allowing the player to move vertically between them.
 */
class Climbable : public EntityFromComponentAux {
public:
    ~Climbable() override = default;

    /**
     * @brief Returns whether this climbable currently accepts climbing attempts.
     * @returns True if active.
     */
    virtual bool is_active_for_player() const = 0;

    /**
     * @brief Checks whether the player can climb upward from a given position.
     * @param position Player position to test.
     * @param h_tolerance Horizontal tolerance around the climbable's x-position.
     * @param v_tolerance Vertical tolerance around the climbable bounds.
     * @returns True if the player is aligned with the climbable for moving upward.
     */
    bool can_climb_up(sf::Vector2f position, float h_tolerance, float v_tolerance) const;

    /**
     * @brief Checks whether the player can climb downward from a given position.
     * @param position Player position to test.
     * @param h_tolerance Horizontal tolerance around the climbable's x-position.
     * @param v_tolerance Vertical tolerance around the climbable bounds.
     * @returns True if the player is aligned with the climbable for moving downward.
     */
    bool can_climb_down(sf::Vector2f position, float h_tolerance, float v_tolerance) const;

    /**
     * @brief Returns the lower platform endpoint of the climbable.
     * @returns Lower end platform.
     */
    std::shared_ptr<Platform> get_lower_end() const { return lower_end; }

    /**
     * @brief Returns the upper platform endpoint of the climbable.
     * @returns Upper end platform.
     */
    std::shared_ptr<Platform> get_upper_end() const { return upper_end; }

    /**
     * @brief Returns the climbable's horizontal position in world space.
     * @returns X coordinate of the climbable center.
     */
    float get_x_pos() const { return x_pos; }

    /**
     * @brief Returns the lower end y-coordinate at the climbable x-position.
     * @returns Surface height of the lower platform at x_pos.
     */
    float get_lower_y_pos() const { return lower_y_pos; }

    /**
     * @brief Returns the upper end y-coordinate at the climbable x-position.
     * @returns Surface height of the upper platform at x_pos.
     */
    float get_upper_y_pos() const { return upper_y_pos; }

protected:
    const std::shared_ptr<Platform> lower_end;
    const std::shared_ptr<Platform> upper_end;
    const float x_pos;
    const float upper_y_pos;
    const float lower_y_pos;

    /**
     * @brief Creates a climbable connection between two platforms.
     * @param lower_end Lower platform endpoint.
     * @param upper_end Upper platform endpoint.
     * @param x_pos Horizontal position of the climbable.
     */
    Climbable(std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_pos);

    Climbable(float lower_y, float upper_y, float x_pos);

private:
    /**
     * @brief Checks whether a position is horizontally aligned with the climbable.
     * @param position Position to test.
     * @param h_tolerance Allowed horizontal error.
     * @returns True if the player's x-coordinate is close enough to the climbable.
     */
    bool can_climb(sf::Vector2f position, float h_tolerance) const;
};

#endif
