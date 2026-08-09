#include "Ladder.hpp"
#include "Constants.hpp"

Ladder::Ladder(Ref<Ladder> ref, std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_pos) :
        RepositoryElement<Ladder>(ref),
        lower_end(lower_end),
        upper_end(upper_end),
        x_pos(x_pos),
        shape() {
    shape.setPosition({x_pos, lower_end->surface_y_at(x_pos)});
    shape.setOrigin({constants::LADDER_WIDTH / 2.f, 0.f});
    shape.setSize({constants::LADDER_WIDTH, upper_end->surface_y_at(x_pos) - lower_end->surface_y_at(x_pos)});
    shape.setFillColor(sf::Color(100, 200, 100)); // light green, stands out on the girders
}

std::shared_ptr<Platform> Ladder::get_lower_end() const {
    return lower_end;
}
std::shared_ptr<Platform> Ladder::get_upper_end() const {
    return upper_end;
}
float Ladder::get_x_pos() const {
    return x_pos;
}
float Ladder::get_lower_y_pos() const {
    return lower_end->surface_y_at(x_pos);
}
float Ladder::get_upper_y_pos() const {
    return upper_end->surface_y_at(x_pos);
}

const sf::RectangleShape& Ladder::get_shape() const {
    return shape;
}
