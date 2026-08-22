#ifndef DISSOLVING_PLATFORM_RENDERER_HPP
#define DISSOLVING_PLATFORM_RENDERER_HPP

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

    void draw(LayerStack &layer_stack) override;

private:
    std::shared_ptr<DissolvingPlatform> entity;
};

#endif
