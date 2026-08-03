#ifndef GAME_H
#define GAME_H

#include <vector>

#include <SFML/Graphics.hpp>

#include "../model/Girder.hpp"
#include "../model/Ladder.hpp"
#include "../view/Layer.hpp"
#include "BarrelControl.hpp"
#include "PlayerControl.hpp"

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

    // build the zig-zag of alternating sloped girders that make up the stage
    static std::vector<Girder> build_girders();

    sf::RenderWindow window;

    // view area and layers
    sf::View view;
    Layer game_layer;

    std::vector<Girder> girders;
    std::vector<Ladder> ladders;

    BarrelControl barrel_control;
    PlayerControl player_control;
};

#endif