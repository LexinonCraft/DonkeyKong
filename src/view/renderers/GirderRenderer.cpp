#include "DK/view/renderers/GirderRenderer.hpp"

#include "DK/Constants.hpp"
#include "DK/util/Positions.hpp"

void GirderRenderer::draw(LayerStack &layer_stack) {
    float width = girder->get_width();
    unsigned int num_steps = static_cast<unsigned int>(width / (constants::GIRDER_THICKNESS * 2.f));
    float step_width = width / num_steps;
    float x = girder->get_left().x;

    AssetsManager::TextureId texture_id;
    switch (girder->get_color()) {
        case Girder::Color::Red:
            texture_id = AssetsManager::TextureId::GirderRed;
            break;
        case Girder::Color::Blue:
            texture_id = AssetsManager::TextureId::GirderBlue;
            break;
    }

    for (unsigned int i = 0; i < num_steps; ++i) {
        sf::Sprite sprite(assets_manager.get_texture(texture_id));
        sprite.setPosition({x + i * step_width, girder->surface_y_at(x + (i + 0.5f) * step_width)});
        set_to_size(sprite, {step_width, constants::GIRDER_THICKNESS});
        layer_stack.get_layer(LayerStack::LayerId::Platforms).add_to_layer(sprite);
    }
}
