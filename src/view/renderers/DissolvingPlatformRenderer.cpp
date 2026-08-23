#include "DK/view/renderers/DissolvingPlatformRenderer.hpp"

#include "DK/Constants.hpp"
#include "DK/model/entities/DissolvingPlatform.hpp"
#include "DK/util/Positions.hpp"
#include "DK/view/LayerStack.hpp"

void DissolvingPlatformRenderer::draw(LayerStack &layer_stack) {
    if (entity->has_dissolved()) {
        return; // Don't draw if the platform has fully dissolved
    }

    sf::RectangleShape shape({entity->get_width(), constants::GIRDER_THICKNESS});
    set_origin(shape, AnchorPosition::TopCenter);
    shape.setPosition(entity->get_position());
    shape.setFillColor(sf::Color::Yellow);
    layer_stack.get_layer(LayerStack::LayerId::Platforms).add_to_layer(shape);
}
