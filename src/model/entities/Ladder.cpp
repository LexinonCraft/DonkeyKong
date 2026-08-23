#include "DK/model/entities/Ladder.hpp"

Ladder::Ladder(Ref ref, std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_pos, bool broken)
    : Ladder(ref, lower_end, upper_end, x_pos, broken, Color::Cyan) {}

Ladder::Ladder(Ref ref, std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_pos, bool broken, Color color)
    : BaseEntity(ref), Climbable(lower_end, upper_end, x_pos), active_for_player(!broken), broken(broken), color(color) {}

Ladder::Ladder(Ref ref, float lower_y, float upper_y, float x_pos, bool broken, Color color, bool active_for_player)
    : BaseEntity(ref), Climbable(lower_y, upper_y, x_pos), active_for_player(active_for_player), broken(broken), color(color) {}

std::unique_ptr<Component<Climbable>> Ladder::create_climbable_component() {
    return std::make_unique<Component<Climbable>>(std::static_pointer_cast<Ladder>(shared_from_this()));
}

void Ladder::check_referenced_entities() {
    if ((lower_end && lower_end->get_entity().is_destroyed()) || (upper_end && upper_end->get_entity().is_destroyed())) {
        destroy();
    }
}
