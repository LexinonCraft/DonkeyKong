#ifndef GIRDER_RENDERER_HPP
#define GIRDER_RENDERER_HPP

#include "DK/model/entities/Girder.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/DrawableComponent.hpp"

/**
 * @brief Renderer for the girder entity.
 */
class GirderRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the girder renderer for a concrete entity.
     * @param girder Girder instance to render.
     * @param assets_manager Assets manager used for retrieving assets.
     */
    GirderRenderer(std::shared_ptr<Girder> girder, AssetsManager &assets_manager) : girder(girder), assets_manager(assets_manager) {}

    /**
     * @brief Draws the girder into the platform layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override;

private:
    std::shared_ptr<Girder> girder;
    AssetsManager &assets_manager;
};

#endif
