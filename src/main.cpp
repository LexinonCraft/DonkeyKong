#include <cstddef>
#include <cstdlib>
#include <ctime>

#include "DK/control/Game.hpp"

/**
 * @brief Entry point for the game.
 * @returns Exit status code for the application.
 */
int main() {
    srand(time(NULL)); // seed the RNG

    Game game;
    game.run();
}
