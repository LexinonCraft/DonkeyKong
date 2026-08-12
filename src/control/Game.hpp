#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "../model/DemoLevel.hpp"
#include "../view/LevelView.hpp"

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
    void start();

private:
    /**
     * @brief Handles keyboard input and updates movement state.
     * @return True if the window was closed, otherwise false.
     */
    bool input();

    /**
     * @brief Advances the model by the elapsed time.
     * @param time_passed Time since the last update in seconds.
     */
    void update(float time_passed);

    /**
     * @brief Draws the current scene to the window.
     */
    void draw();

    sf::RenderWindow window;
    DemoLevel *level;
    sf::View view;
    LevelView level_view;
};

#endif