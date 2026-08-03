#include "BarrelControl.hpp"

#include "../model/Constants.hpp"

BarrelControl::BarrelControl(Layer& layer) :
    layer(layer),
    barrel() {
}

void BarrelControl::spawn(const std::vector<Girder>& girders) {
    // Reassigning the unique_ptr destroys the previous barrel (if any).
    sf::Vector2f top = girders[0].high_end();
    barrel = std::make_unique<Barrel>(
        sf::Vector2f{top.x, top.y - constants::BARREL_RADIUS});
}

void BarrelControl::update(float dt, const std::vector<Girder>& girders) {
    barrel->update(dt, girders);

    // once the barrel has dropped below the bottom of the screen (y = 0),
    // throw it away and roll a new one from the top
    if (barrel->get_position().y - constants::BARREL_RADIUS > 0.f) {
        spawn(girders);
    }
}

void BarrelControl::draw() {
    layer.add_to_layer(barrel->get_shape());
}
