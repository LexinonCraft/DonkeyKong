#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "../model/Level.hpp"
#include "../view/LevelView.hpp"

// Game class
class Game {

public:
    //initialize the game (window and controls)
    Game();

    void start();

private:
    // processes user input, returns true if window has been closed
    bool input();

    // updates all game elements
    void update(float time_passed);

    // draws the scene
    void draw();

    sf::RenderWindow window;

    Level *level;

    // view area and layers
    sf::View view;
    LevelView level_view;
};

#endif