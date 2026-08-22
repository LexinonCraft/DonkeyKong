#ifndef GAME_OVER_VIEW_HPP
#define GAME_OVER_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "DK/view/AbstractSceneView.hpp"
#include "DK/view/AssetsManager.hpp"

class GameOverView : public AbstractSceneView {
public:
    GameOverView(sf::RenderWindow &window, AssetsManager &assets_manager) : AbstractSceneView(window, assets_manager) {};

    void draw();
};

#endif
