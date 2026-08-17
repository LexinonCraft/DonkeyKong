#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "../model/PlayerData.hpp"
#include "../control/AbstractSceneControl.hpp"
#include "../view/AssetsManager.hpp"

/**
 * @brief Main controller for the Donkey Kong-style game loop.
 *
 * The game owns the window, the demo level, and the view state used by the
 * render pipeline.
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
    sf::Clock clock;
    sf::RenderWindow window;
    AssetsManager assets_manager;
    std::unique_ptr<AbstractSceneControl> scene_control;
    PlayerData player_data;

    bool input();

    void handle_next_scene(AbstractSceneControl::NextScene next_scene);
};

#endif