#include "Ladder.hpp"
#include "../Constants.hpp"

Ladder::Ladder(Ref ref, std::weak_ptr<Platform> lower_end, std::weak_ptr<Platform> upper_end, float x_pos) :
        BaseEntity(ref),
        Climbable(lower_end, upper_end, x_pos),
        shape() {
    shape.setPosition({x_pos, lower_end.lock()->surface_y_at(x_pos)});
    shape.setOrigin({constants::LADDER_WIDTH / 2.f, 0.f});
    shape.setSize({constants::LADDER_WIDTH, upper_end.lock()->surface_y_at(x_pos) - lower_end.lock()->surface_y_at(x_pos)});
    shape.setFillColor(sf::Color(100, 200, 100)); // light green, stands out on the girders
}
