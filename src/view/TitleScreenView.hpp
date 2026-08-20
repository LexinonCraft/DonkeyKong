#ifndef TITLE_SCREEN_VIEW_HPP
#define TITLE_SCREEN_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetsManager.hpp"
#include "AbstractSceneView.hpp"

class TitleScreenView : public AbstractSceneView {
public:
    TitleScreenView(sf::RenderWindow &window, AssetsManager &assets_manager) : AbstractSceneView(window, assets_manager) {};

    void draw(float animation_timer);
};

#endif
