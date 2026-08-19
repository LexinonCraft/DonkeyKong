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
        const sf::Vector2f position = hammer->get_position();

        sf::RectangleShape handle({4.f, 15.f});
        handle.setOrigin({2.f, 15.f});
        handle.setPosition(position);
        handle.setFillColor(sf::Color(130, 75, 35));

        sf::RectangleShape head({constants::HAMMER_WIDTH, 7.f});
        head.setOrigin({constants::HAMMER_WIDTH / 2.f, 7.f});
        head.setPosition({position.x, position.y - 13.f});
        head.setFillColor(sf::Color(240, 200, 60));

        layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(handle);
        layer_stack.get_layer(LayerStack::LayerId::Objects).add_to_layer(head);
    }

private:
    std::shared_ptr<HammerPowerUp> hammer;
};

#endif
