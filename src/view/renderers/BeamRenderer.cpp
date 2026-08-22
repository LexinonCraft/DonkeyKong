#include "DK/view/renderers/BeamRenderer.hpp"

#include "DK/util/Positions.hpp"

void BeamRenderer::draw(LayerStack &layer_stack) {
    sf::RectangleShape shape({constants::BEAM_WIDTH, beam->get_lower_y() - beam->get_upper_y()});
    set_origin(shape, AnchorPosition::TopCenter);
    shape.setPosition({beam->get_x(), beam->get_upper_y()});
    shape.setFillColor(sf::Color::Cyan);

    layer_stack.get_layer(LayerStack::LayerId::Ladders).add_to_layer(shape);
}
