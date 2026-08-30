#include "DK/model/components/Climbable.hpp"

#include <utility>

bool Climbable::can_climb_up(sf::Vector2f position, float h_tolerance, float v_tolerance) const {
    return can_climb(position, h_tolerance) && position.y < get_lower_y_pos() + v_tolerance && position.y > get_upper_y_pos() + v_tolerance;
}

bool Climbable::can_climb_down(sf::Vector2f position, float h_tolerance, float v_tolerance) const {
    return can_climb(position, h_tolerance) && position.y < get_lower_y_pos() - v_tolerance && position.y > get_upper_y_pos() - v_tolerance;
}

Climbable::Climbable(std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_pos)
    : lower_end(std::move(lower_end)), upper_end(std::move(upper_end)), x_pos(x_pos), upper_y_pos(this->upper_end->surface_y_at(x_pos)),
      lower_y_pos(this->lower_end->surface_y_at(x_pos)) {}

Climbable::Climbable(float lower_y, float upper_y, float x_pos)
    : lower_end(nullptr), upper_end(nullptr), x_pos(x_pos), upper_y_pos(upper_y), lower_y_pos(lower_y) {}

bool Climbable::can_climb(sf::Vector2f position, float h_tolerance) const {
    return is_active_for_player() && position.x < x_pos + h_tolerance && position.x > x_pos - h_tolerance;
}
