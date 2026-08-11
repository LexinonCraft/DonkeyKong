#ifndef CLIMBABLE_HPP
#define CLIMBABLE_HPP

#include <memory>

#include "../components/Platform.hpp"
#include "../util/EntityFromComponentAux.hpp"

class Climbable : public EntityFromComponentAux {
public:
    virtual ~Climbable() {}

    virtual bool is_active() const = 0;

    bool can_climb_up(sf::Vector2f position, float h_tolerance, float v_tolerance) const {
        return can_climb(position, h_tolerance) && position.y < get_lower_y_pos() + v_tolerance && position.y > get_upper_y_pos() + v_tolerance;
    }

    bool can_climb_down(sf::Vector2f position, float h_tolerance, float v_tolerance) const {
        return can_climb(position, h_tolerance) && position.y < get_lower_y_pos() - v_tolerance && position.y > get_upper_y_pos() - v_tolerance;
    }

    std::shared_ptr<Platform> get_lower_end() const {
        return lower_end;
    }

    std::shared_ptr<Platform> get_upper_end() const {
        return upper_end;
    }

    float get_x_pos() const {
        return x_pos;
    }

    float get_lower_y_pos() const {
        return lower_end->surface_y_at(x_pos);
    }

    float get_upper_y_pos() const {
        return upper_end->surface_y_at(x_pos);
    }

protected:
    const std::shared_ptr<Platform> lower_end;
    const std::shared_ptr<Platform> upper_end;
    const float x_pos;

    Climbable(std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_pos)
        : lower_end(lower_end), upper_end(upper_end), x_pos(x_pos) {}

private:
    bool can_climb(sf::Vector2f position, float h_tolerance) const {
        return is_active() && position.x < x_pos + h_tolerance && position.x > x_pos - h_tolerance;
    }
};

#endif
