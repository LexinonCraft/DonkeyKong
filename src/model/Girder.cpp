#include "Girder.hpp"

#include <cmath>
#include <SFML/Graphics/Color.hpp>

#include "Constants.hpp"
#include "visitor/PlatformVisitor.hpp"

Girder::Girder(Ref<Platform> ref, sf::Vector2f left, sf::Vector2f right) :
    Platform(ref),
    left(left),
    right(right),
    shape() {
        // build the tilted bar: a rectangle from `left` to `right`, rotated to match
        float dx = right.x - left.x;
        float dy = right.y - left.y;
        float length = std::sqrt(dx * dx + dy * dy);

        shape.setSize({length, constants::GIRDER_THICKNESS});
        shape.setOrigin({0.f, constants::GIRDER_THICKNESS / 2.f});
        shape.setPosition(left);
        shape.setRotation(sf::radians(std::atan2(dy, dx)));
        shape.setFillColor(sf::Color(200, 80, 40));
}

float Girder::slope_at(float x) const {
    return (right.y - left.y) / (right.x - left.x);
}

float Girder::surface_y_at(float x) const {
    return left.y + slope_at(x) * (x - left.x);
}

bool Girder::covers_x(float x) const {
    return x >= left.x && x <= right.x;
}

int Girder::downhill_sign() const {
    // the lower end has the larger y; roll toward it
    return (right.y > left.y) ? 1 : -1;
}

sf::Vector2f Girder::high_end() const {
    // the upper end has the smaller y
    return (left.y <= right.y) ? left : right;
}

bool Girder::is_active() const {
    return true;
}

sf::Vector2f Girder::displacement_at(float x, float dt) const {
    // the girder is static, so no displacement
    return {0.f, 0.f};
}

void Girder::update(float dt) {
    // the girder is static, so no update needed
}

void Girder::accept(PlatformVisitor &visitor) const {
    visitor.visit(*this);
}

const sf::RectangleShape& Girder::get_shape() const {
    return shape;
}
