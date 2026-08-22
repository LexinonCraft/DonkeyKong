#ifndef BEAM_RENDERER_HPP
#define BEAM_RENDERER_HPP

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>

#include "DK/model/entities/Beam.hpp"
#include "DK/view/DrawableComponent.hpp"

class BeamRenderer : public DrawableComponent {
public:
    BeamRenderer(std::shared_ptr<Beam> beam) : beam(beam) {}

    void draw(LayerStack &layer_stack) override {
        sf::RectangleShape shape({constants::BEAM_WIDTH, beam->get_lower_y() - beam->get_upper_y()});
        sf::FloatRect bounds = shape.getLocalBounds();
        shape.setOrigin({bounds.size.x / 2.f, 0.f});
        shape.setPosition({beam->get_x(), beam->get_upper_y()});
        shape.setFillColor(sf::Color::Cyan);

        layer_stack.get_layer(LayerStack::LayerId::Ladders).add_to_layer(shape);
    }

private:
    std::shared_ptr<Beam> beam;
};

#endif
