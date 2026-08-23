#ifndef GAME_HPP
#define GAME_HPP

#include "DK/control/AbstractSceneControl.hpp"
#include "DK/model/PlayerData.hpp"
#include "DK/view/AssetsManager.hpp"

/**
 * @brief Main controller for the game loop.
 *
 * Owns the window, assets manager, player data, and scene control. The game loop is run in the run() method, which handles input, updates
 * the scene, and draws the scene.
 */
class Game {
public:
    /**
     * @brief Initialises the application window, level, and view.
     */
    Game();

    /**
     * @brief Runs the main game loop until the window is closed.
     */
    void run();

private:
    sf::RenderWindow window;
    AssetsManager assets_manager;
    PlayerData player_data;
    std::unique_ptr<AbstractSceneControl> scene_control;

    /**
     * @brief Handle input
     *
     * @return true if the game should quit
     * @return false otherwise
     */
    bool input();

    /**
     * @brief Handle the potential transition to the next scene.
     *
     * @param next_scene The transition instruction from the current scene control.
     */
    void handle_next_scene(AbstractSceneControl::NextScene next_scene);
};

#endif
