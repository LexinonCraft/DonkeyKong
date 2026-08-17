#include "Ladder.hpp"
#include "../../Constants.hpp"

Ladder::Ladder(Ref ref, std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_pos, bool broken) :
        BaseEntity(ref),
        Climbable(lower_end, upper_end, x_pos),
        shape(),
        broken(broken) {
    shape.setPosition({x_pos, lower_end->surface_y_at(x_pos)});
    shape.setOrigin({constants::LADDER_WIDTH / 2.f, 0.f});
    shape.setSize({constants::LADDER_WIDTH, upper_end->surface_y_at(x_pos) - lower_end->surface_y_at(x_pos)});
    shape.setFillColor(broken ? sf::Color(100, 100, 100) : sf::Color(100, 200, 100));
}

void Ladder::check_referenced_entities() {
    if (lower_end->get_entity().is_destroyed() || upper_end->get_entity().is_destroyed()) {
        destroy();
    }
}
