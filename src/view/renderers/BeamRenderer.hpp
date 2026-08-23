#ifndef BEAM_RENDERER_HPP
#define BEAM_RENDERER_HPP

#include <memory>

#include <SFML/Graphics/RectangleShape.hpp>

#include "DK/model/Declarations.hpp"
#include "DK/view/DrawableComponent.hpp"

/**
 * @brief Renderer for the beam entity.
 */
class BeamRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the beam renderer for a concrete entity.
     * @param beam Beam instance to render.
     */
    BeamRenderer(std::shared_ptr<Beam> beam) : beam(beam) {}

    void draw(LayerStack &layer_stack) override;

private:
    std::shared_ptr<Beam> beam;
};

#endif
