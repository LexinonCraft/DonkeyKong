#ifndef STAGE_VIEW_HPP
#define STAGE_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetsManager.hpp"
#include "AbstractSceneView.hpp"
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
    void draw();

    void update(float dt);

private:
    DrawableComponentRepository drawable_components;
    Stage &stage;
};

#endif
