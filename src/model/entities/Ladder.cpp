#include "DK/model/entities/Ladder.hpp"

#include "DK/Constants.hpp"

Ladder::Ladder(Ref ref, std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_pos, bool broken)
    : Ladder(ref, lower_end, upper_end, x_pos, broken, Color::Cyan) {}

Ladder::Ladder(Ref ref, std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_pos, bool broken, Color color)
    : BaseEntity(ref), Climbable(lower_end, upper_end, x_pos), shape(), active_for_player(!broken), broken(broken), color(color) {
    shape.setPosition({x_pos, lower_end->surface_y_at(x_pos)});
    shape.setOrigin({constants::LADDER_WIDTH / 2.f, 0.f});
    shape.setSize({constants::LADDER_WIDTH, upper_end->surface_y_at(x_pos) - lower_end->surface_y_at(x_pos)});
    shape.setFillColor(broken ? sf::Color(100, 100, 100) : sf::Color(100, 200, 100)); // TODO: remove this since we are using textures
}

Ladder::Ladder(Ref ref, float lower_y, float upper_y, float x_pos, bool broken, Color color, bool active_for_player)
    : BaseEntity(ref), Climbable(lower_y, upper_y, x_pos), shape(), active_for_player(active_for_player), broken(broken), color(color) {
    shape.setPosition({x_pos, lower_y});
    shape.setOrigin({constants::LADDER_WIDTH / 2.f, 0.f});
    shape.setSize({constants::LADDER_WIDTH, upper_y - lower_y});
    shape.setFillColor(broken ? sf::Color(100, 100, 100) : sf::Color(100, 200, 100));
}

void Ladder::check_referenced_entities() {
    if ((lower_end && lower_end->get_entity().is_destroyed()) || (upper_end && upper_end->get_entity().is_destroyed())) {
        destroy();
    }
}
