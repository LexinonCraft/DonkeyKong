#ifndef DISSOLVING_PLATFORM_RENDERER_HPP
#define DISSOLVING_PLATFORM_RENDERER_HPP

#include "DK/Constants.hpp"
#include "DK/model/entities/DissolvingPlatform.hpp"
#include "DK/view/DrawableComponent.hpp"
#include "DK/view/LayerStack.hpp"

/**
 * @brief Renderer for the dissolving platform entity.
 */
class DissolvingPlatformRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the dissolving platform renderer for a concrete entity.
     * @param entity Dissolving platform instance to render.
     */
    DissolvingPlatformRenderer(std::shared_ptr<DissolvingPlatform> entity) : entity(entity) {}

    void draw(LayerStack &layer_stack) override {
        if (entity->has_dissolved()) {
            return; // Don't draw if the platform has fully dissolved
        }

        sf::RectangleShape shape({entity->get_width(), constants::GIRDER_THICKNESS});
        sf::FloatRect bounds = shape.getLocalBounds();
        shape.setOrigin({bounds.size.x / 2.f, 0.f});
        shape.setPosition(entity->get_position());
        shape.setFillColor(sf::Color::Yellow);
        layer_stack.get_layer(LayerStack::LayerId::Platforms).add_to_layer(shape);
    }

private:
    std::shared_ptr<DissolvingPlatform> entity;
};

#endif
