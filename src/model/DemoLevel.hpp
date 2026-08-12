#ifndef DEMO_LEVEL_HPP
#define DEMO_LEVEL_HPP

#include "Level.hpp"

/**
 * @brief Concrete test level used for the current prototype.
 *
 * This level constructs a small set of girders and ladders and places the game
 * objects needed to exercise the movement and climbing logic.
 */
class DemoLevel : public Level {
public:
    /**
     * @brief Creates the demo scene for the level.
     * @param id_generator Function used to allocate entity ids.
     */
    DemoLevel(Id id_generator());
};

#endif
