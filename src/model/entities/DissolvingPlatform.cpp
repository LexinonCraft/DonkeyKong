#include "DK/model/entities/DissolvingPlatform.hpp"

#include <SFML/Graphics/Color.hpp>

#include "DK/Constants.hpp"

DissolvingPlatform::DissolvingPlatform(Ref ref, sf::Vector2f position, float width)
    : BaseEntity(ref), position(position), width(width), shape() {
    shape.setSize({width, constants::GIRDER_THICKNESS});
    shape.setOrigin({0.f, constants::GIRDER_THICKNESS / 2.f});
    shape.setPosition(position);
    shape.setFillColor(sf::Color(200, 80, 40));
}

float DissolvingPlatform::slope_at(float x) const { return 0.f; }

float DissolvingPlatform::surface_y_at(float x) const { return position.y; }

bool DissolvingPlatform::covers_x(float x, float h_tolerance_left, float h_tolerance_right) const {
    return x >= position.x - width / 2.f - h_tolerance_left && x <= position.x + width / 2.f + h_tolerance_right;
}

int DissolvingPlatform::downhill_sign() const { return 0; }

sf::Vector2f DissolvingPlatform::high_end() const {
    // the upper end has the smaller y
    return position; // for a horizontal platform, both ends have the same y
}

bool DissolvingPlatform::is_active() const { return true; }

sf::Vector2f DissolvingPlatform::displacement_at(float x, float dt) const {
    // the platform is static, so no displacement
    return {0.f, 0.f};
}

void DissolvingPlatform::accept(EntityVisitor &visitor) { visitor.visit(*this); }

const sf::RectangleShape &DissolvingPlatform::get_shape() const { return shape; }
