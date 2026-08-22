#ifndef GAME_OVER_VIEW_HPP
#define GAME_OVER_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "DK/view/AssetsManager.hpp"
#include "DK/view/views/AbstractSceneView.hpp"

/**
 * @brief View for the game over screen
 */
class GameOverView : public AbstractSceneView {
public:
    /**
     * @brief Initializes the GameOverView with the given window and assets manager
     *
     * @param window The window to draw to
     * @param assets_manager The assets manager to retrieve assets from
     */
    GameOverView(sf::RenderWindow &window, AssetsManager &assets_manager) : AbstractSceneView(window, assets_manager) {}

    /**
     * @brief Draws the game over screen
     */
    void draw();
};

#endif
