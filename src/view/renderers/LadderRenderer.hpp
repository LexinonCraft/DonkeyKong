#ifndef LADDER_RENDERER_HPP
#define LADDER_RENDERER_HPP

#include "DK/model/entities/Ladder.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/DrawableComponent.hpp"

/**
 * @brief Renderer for the ladder entity.
 */
class LadderRenderer : public DrawableComponent {
public:
    /**
     * @brief Creates the ladder renderer for a concrete entity.
     * @param ladder Ladder instance to render.
     * @param assets_manager Assets manager used for retrieving assets.
     */
    LadderRenderer(std::shared_ptr<Ladder> ladder, AssetsManager &assets_manager) : ladder(ladder), assets_manager(assets_manager) {}

    /**
     * @brief Draws the ladder into the ladder layer.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw(LayerStack &layer_stack) override;

private:
    std::shared_ptr<Ladder> ladder;
    AssetsManager &assets_manager;

    /**
     * @brief Draw a continuous section of the ladder into the ladder layer.
     *
     * @param x The x position of the ladder.
     * @param lower_y The lower y position of the ladder section.
     * @param upper_y The upper y position of the ladder section.
     * @param layer_stack Layer stack used for rendering.
     */
    void draw_raw(float x, float lower_y, float upper_y, LayerStack &layer_stack);
};

#endif
