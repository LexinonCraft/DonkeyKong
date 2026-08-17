#ifndef STAGE_TRANSITION_VIEW_HPP
#define STAGE_TRANSITION_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetsManager.hpp"
#include "AbstractSceneView.hpp"
#include "../model/PlayerData.hpp"

class StageTransitionView : public AbstractSceneView {
public:
    StageTransitionView(sf::RenderWindow &window, AssetsManager &assets_manager, PlayerData &player_data) 
        : AbstractSceneView(window, assets_manager), player_data(player_data) {};

    void draw();

private:
    PlayerData &player_data;
};

#endif
