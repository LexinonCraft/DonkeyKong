#ifndef STAGE_TRANSITION_VIEW_HPP
#define STAGE_TRANSITION_VIEW_HPP

#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include "DK/model/PlayerData.hpp"
#include "DK/model/StageSequence.hpp"
#include "DK/view/Declarations.hpp"
#include "DK/view/views/AbstractSceneView.hpp"

/**
 * @brief View for the stage transition scene, which displays the current stage and the player's progress.
 */
class StageTransitionView : public AbstractSceneView {
public:
    /**
     * @brief Initializes the StageTransitionView with the given window, assets manager, and player data.
     *
     * @param window The window to draw to.
     * @param assets_manager The assets manager to retrieve assets.
     * @param player_data A reference to the global player data, which is used to determine the current stage and level.
     */
    StageTransitionView(sf::RenderWindow &window, AssetsManager &assets_manager, PlayerData &player_data)
        : AbstractSceneView(window, assets_manager), stage_sequence(get_stage_sequence(player_data.get_level())),
          stage_in_level(player_data.get_stage_in_level()) {}

    /**
     * @brief Draw the stage transition view.
     */
    void draw();

private:
    std::unique_ptr<std::vector<StageId>> stage_sequence;
    unsigned int stage_in_level;
};

#endif
