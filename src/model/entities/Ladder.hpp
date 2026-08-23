#ifndef LADDER_HPP
#define LADDER_HPP

#include <memory>

#include "DK/model/components/Climbable.hpp"
#include "DK/model/components/Platform.hpp"
#include "DK/model/util/BaseEntity.hpp"

/// @brief Represents a ladder connecting two girders at a specific x position.
class Ladder : public BaseEntity, public Climbable {
public:
    enum class Color {
        Cyan,
        Yellow,
    };

    Ladder(Ref ref, std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_pos, bool broken);

    Ladder(Ref ref, std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_pos, bool broken, Color color);

    Ladder(Ref ref, float lower_y, float upper_y, float x_pos, bool broken, Color color, bool active_for_player);

    bool is_active_for_player() const override { return active_for_player; }

    void accept(EntityVisitor &visitor) override { visitor.visit(*this); }

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
