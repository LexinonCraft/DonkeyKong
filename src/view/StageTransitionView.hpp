#ifndef STAGE_TRANSITION_VIEW_HPP
#define STAGE_TRANSITION_VIEW_HPP

#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetsManager.hpp"
#include "AbstractSceneView.hpp"
#include "../model/PlayerData.hpp"
#include "../model/StageSequence.hpp"

class StageTransitionView : public AbstractSceneView {
public:
    StageTransitionView(sf::RenderWindow &window, AssetsManager &assets_manager, PlayerData &player_data) 
        : AbstractSceneView(window, assets_manager), stage_sequence(get_stage_sequence(player_data.get_level())), stage_in_level(player_data.get_stage_in_level()) {}

    void draw();

private:
    std::unique_ptr<std::vector<StageId>> stage_sequence;
    unsigned int stage_in_level;
};

#endif
