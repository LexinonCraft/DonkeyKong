#include <cstddef>
#include <cstdlib>
#include <ctime>

#include "control/Game.hpp"

/**
 * @brief Entry point for the Donkey Kong-style game.
 * @return Exit status code for the application.
 */
int main() {
    srand(time(NULL)); // seed the RNG

    Game game;
    game.run();
}