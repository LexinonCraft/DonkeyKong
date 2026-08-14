#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

#include "../control/AbstractSceneControl.hpp"
#include "../view/TextureRegistry.hpp"

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

    TextureRegistry &get_texture_registry() { return texture_registry; }

private:
    sf::Clock clock;
    sf::RenderWindow window;
    TextureRegistry texture_registry;
    std::unique_ptr<AbstractSceneControl> scene_control;
};

#endif