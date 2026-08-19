#ifndef HAMMER_RENDERER_HPP
#define HAMMER_RENDERER_HPP

#include <memory>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "../Constants.hpp"
#include "../model/entities/HammerPowerUp.hpp"
#include "DrawableComponent.hpp"

class HammerRenderer : public DrawableComponent {
public:
    HammerRenderer(std::shared_ptr<HammerPowerUp> hammer) : hammer(hammer) {}

    void draw(LayerStack &layer_stack) override {
        sf::RectangleShape shape({constants::HAMMER_WIDTH, constants::HAMMER_HEIGHT});
        shape.setOrigin({constants::HAMMER_WIDTH / 2.f, constants::HAMMER_HEIGHT});
        shape.setPosition(hammer->get_position());
        shape.setFillColor(sf::Color(240, 200, 60));
        layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(shape);
    }

private:
    std::shared_ptr<HammerPowerUp> hammer;
};

#endif
