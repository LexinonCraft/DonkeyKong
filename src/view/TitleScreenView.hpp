#ifndef TITLE_SCREEN_VIEW_HPP
#define TITLE_SCREEN_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "DK/model/PlayerData.hpp"
#include "DK/view/AbstractSceneView.hpp"
#include "DK/view/AssetsManager.hpp"

class TitleScreenView : public AbstractSceneView {
public:
    TitleScreenView(sf::RenderWindow &window, AssetsManager &assets_manager, PlayerData &player_data)
        : AbstractSceneView(window, assets_manager), player_data(player_data) {};

    void draw(float animation_timer);

private:
    PlayerData &player_data;
};

#endif
