#include "DK/model/entities/HammerPowerUp.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "DK/Constants.hpp"
#include "DK/model/util/EntityVisitor.hpp"

HammerPowerUp::HammerPowerUp(Ref ref, sf::Vector2f position)
    : BaseEntity(ref), position(position), shape({constants::HAMMER_WIDTH, constants::HAMMER_HEIGHT}) {
    shape.setOrigin({constants::HAMMER_WIDTH / 2.f, constants::HAMMER_HEIGHT});
    shape.setPosition(position);
    shape.setFillColor(sf::Color(240, 200, 60));
}

bool HammerPowerUp::touches(const sf::RectangleShape &player_shape) const {
    return shape.getGlobalBounds().findIntersection(player_shape.getGlobalBounds()).has_value();
}

void HammerPowerUp::on_picked_up() { destroy(); }

void HammerPowerUp::accept(EntityVisitor &visitor) { visitor.visit(*this); }
