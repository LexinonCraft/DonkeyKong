#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

/**
 * @brief Gameplay and rendering constants used throughout the project.
 *
 * The coordinate system follows SFML conventions where the positive y axis points
 * downward, so gravity also points downward in world space.
 */
namespace constants {
    constexpr int VIEW_WIDTH = 600;
    constexpr int VIEW_HEIGHT = 600;
    constexpr unsigned int FRAME_RATE = 60;
    constexpr float TARGET_ASPECT_RATIO = static_cast<float>(VIEW_WIDTH) / static_cast<float>(VIEW_HEIGHT);

    // barrel / girder physics (increment 2). Remember: the view is y-inverted,
    // so +y points downward (toward the bottom of the screen) = gravity direction.
    constexpr float BARREL_RADIUS = 12.f;     // px
    constexpr float ROLL_SPEED = 160.f;       // px/sec, constant horizontal roll on a girder
    constexpr float GRAVITY = 900.f;          // px/sec^2, applied while falling
    constexpr float GIRDER_THICKNESS = 12.f;  // px

    constexpr float PLAYER_WIDTH = 20.f;        // px
    constexpr float PLAYER_HEIGHT = 32.f;       // px
    constexpr float PLAYER_JUMP_SPEED = 300.f;  // px/sec, initial jump
    constexpr float PLAYER_WALKING_SPEED = 120.f;  // px/sec, horizontal speed while on a girder
    constexpr float PLAYER_CLIMBING_SPEED = 100.f; // px/sec, vertical speed while climbing a ladder

    constexpr float LADDER_WIDTH = 10.f;  // px

    constexpr unsigned int INITIAL_LIVES = 3;  // starting lives for the player
}

#endif
