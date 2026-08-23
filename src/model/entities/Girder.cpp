#include "DK/model/entities/Girder.hpp"

#include <cmath>
#include <cstdlib>

Girder::Girder(Ref ref, sf::Vector2f left, sf::Vector2f right) : Girder(ref, left, right, Color::Red) {}

Girder::Girder(Ref ref, sf::Vector2f left, sf::Vector2f right, Color color) : BaseEntity(ref), left(left), right(right), color(color) {}

float Girder::slope_at(float x) const { return (right.y - left.y) / (right.x - left.x); }

float Girder::surface_y_at(float x) const { return left.y + slope_at(x) * (x - left.x); }

bool Girder::covers_x(float x, float h_tolerance_left, float h_tolerance_right) const {
    return x >= left.x - h_tolerance_left && x <= right.x + h_tolerance_right;
}

int Girder::downhill_sign() const {
    // the lower end has the larger y; roll toward it
    if (std::abs(right.y - left.y) < 1e-6f) {
        return 0; // flat
    }
    return (right.y > left.y) ? 1 : -1;
}

sf::Vector2f Girder::high_end() const {
    // the upper end has the smaller y
    return (left.y <= right.y) ? left : right;
}

bool Girder::is_active() const { return true; }

sf::Vector2f Girder::displacement_at(float x, float dt) const {
    // the girder is static, so no displacement
    return {0.f, 0.f};
}

void Girder::accept(EntityVisitor &visitor) { visitor.visit(*this); }

std::unique_ptr<Component<Platform>> Girder::create_platform_component() {
    return std::make_unique<Component<Platform>>(std::static_pointer_cast<Girder>(shared_from_this()));
}
