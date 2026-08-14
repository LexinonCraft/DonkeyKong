#ifndef STAGE_VIEW_HPP
#define STAGE_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetsManager.hpp"
#include "AbstractSceneView.hpp"
#include "LayerStack.hpp"
#include "../model/Stage.hpp"
#include "DrawableComponentRepository.hpp"

/**
 * @brief View component that renders a whole stage using layered SFML textures.
 */
class StageView : public AbstractSceneView {
public:
    /**
     * @brief Creates the stage view and binds it to a specific stage.
     * @param window Window used for rendering.
     * @param stage Stage whose entities are rendered.
     */
    StageView(sf::RenderWindow &window, Stage &stage, AssetsManager &assets_manager);

    /**
     * @brief Renders the current state of the stage.
     */
    void draw() override;

    /**
     * @brief Applies the active camera view to every render layer.
     * @param view Camera to use for the rendering scene.
     */
    void set_view(const sf::View &view) override;

private:
    LayerStack layer_stack;
    sf::RenderWindow &window;
    DrawableComponentRepository drawable_components;
};

#endif
