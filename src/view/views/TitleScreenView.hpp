#ifndef TITLE_SCREEN_VIEW_HPP
#define TITLE_SCREEN_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "DK/model/Declarations.hpp"
#include "DK/view/Declarations.hpp"
#include "DK/view/views/AbstractSceneView.hpp"

/**
 * @brief View for the title screen.
 */
class TitleScreenView : public AbstractSceneView {
public:
    /**
     * @brief Initializes the title screen view with the given window, assets manager, and player data.
     *
     * @param window The window to draw to.
     * @param assets_manager The assets manager to retrieve assets from.
     * @param player_data A reference to the global player data.
     */
    TitleScreenView(sf::RenderWindow &window, AssetsManager &assets_manager, PlayerData &player_data)
        : AbstractSceneView(window, assets_manager), player_data(player_data) {}

    /**
     * @brief Draw the title screen.
     *
     * @param animation_timer Timer for the Donkey Kong animation.
     */
    void draw(float animation_timer);

private:
    PlayerData &player_data;
};

#endif
