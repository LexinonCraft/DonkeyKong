#include "DK/view/renderers/BeamRenderer.hpp"

void BeamRenderer::draw(LayerStack &layer_stack) {
    sf::RectangleShape shape({constants::BEAM_WIDTH, beam->get_lower_y() - beam->get_upper_y()});
    sf::FloatRect bounds = shape.getLocalBounds();
    shape.setOrigin({bounds.size.x / 2.f, 0.f});
    shape.setPosition({beam->get_x(), beam->get_upper_y()});
    shape.setFillColor(sf::Color::Cyan);

    layer_stack.get_layer(LayerStack::LayerId::Ladders).add_to_layer(shape);
}
