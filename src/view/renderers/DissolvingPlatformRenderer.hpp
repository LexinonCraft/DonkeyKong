#ifndef DISSOLVING_PLATFORM_RENDERER_HPP
#define DISSOLVING_PLATFORM_RENDERER_HPP

#include <memory>

#include "DK/model/Declarations.hpp"
#include "DK/view/Declarations.hpp"
#include "DK/view/DrawableComponent.hpp"

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

    void draw(LayerStack &layer_stack) override;

private:
    std::shared_ptr<DissolvingPlatform> entity;
};

#endif
