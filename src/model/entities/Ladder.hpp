#ifndef LADDER_HPP
#define LADDER_HPP

#include <memory>

#include "DK/model/Declarations.hpp"
#include "DK/model/components/Climbable.hpp"
#include "DK/model/util/BaseEntity.hpp"

/**
 * @brief Climbable ladder spanning two vertical endpoints at a fixed horizontal position.
 *
 * A ladder can connect two platforms or use endpoint coordinates. A ladder
 * created with coordinates has no platform references, so get_lower_end()
 * and get_upper_end() return nullptr here.
 */
class Ladder : public BaseEntity, public Climbable {
public:
    enum class Color {
        Cyan,
        Yellow,
    };

    /**
     * @brief Creates a cyan ladder connecting two platforms.
     * @param ref Repository reference assigned to the ladder.
     * @param lower_end Lower platform endpoint.
     * @param upper_end Upper platform endpoint.
     * @param x_pos Horizontal position of the ladder.
     * @param broken Whether the ladder is broken.
     */
    Ladder(Ref ref, std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_pos, bool broken);

    /**
     * @brief Creates a ladder connecting two platforms.
     * @param ref Repository reference assigned to the ladder.
     * @param lower_end Lower platform endpoint.
     * @param upper_end Upper platform endpoint.
     * @param x_pos Horizontal position of the ladder.
     * @param broken Whether the ladder is broken.
     * @param color Color of the ladder.
     */
    Ladder(Ref ref, std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_pos, bool broken, Color color);

    /**
     * @brief Creates a ladder from endpoint coordinates without platform references.
     * @param ref Repository reference assigned to the ladder.
     * @param lower_y Lower endpoint y-coordinate.
     * @param upper_y Upper endpoint y-coordinate.
     * @param x_pos Horizontal position of the ladder.
     * @param broken Whether the ladder is broken.
     * @param color Color of the ladder.
     * @param active_for_player Whether the player can use the ladder.
     */
    Ladder(Ref ref, float lower_y, float upper_y, float x_pos, bool broken, Color color, bool active_for_player);

    bool is_active_for_player() const override { return active_for_player; }

    void accept(EntityVisitor &visitor) override;

    void check_referenced_entities() override;

    BaseEntity &get_entity() override { return *this; }

    std::unique_ptr<Component<Climbable>> create_climbable_component() override;

    Color get_color() const { return color; }

    bool is_broken() const { return broken; }

    bool is_secondary_entity() const override { return false; }

private:
    bool active_for_player;
    bool broken;
    Color color;
};
#endif
