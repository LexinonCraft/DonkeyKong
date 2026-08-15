#ifndef STAGE_TRANSITION_VIEW_HPP
#define STAGE_TRANSITION_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetsManager.hpp"
#include "AbstractSceneView.hpp"

class StageTransitionView : public AbstractSceneView {
public:
    StageTransitionView(sf::RenderWindow &window, AssetsManager &assets_manager) : AbstractSceneView(window, assets_manager) {};

    void draw();
};

#endif
