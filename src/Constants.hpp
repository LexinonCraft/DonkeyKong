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
    constexpr int VIEW_HEIGHT = 800;
    constexpr unsigned int FRAME_RATE = 60;
    constexpr float TARGET_ASPECT_RATIO = static_cast<float>(VIEW_WIDTH) / static_cast<float>(VIEW_HEIGHT);

    // barrel / girder physics (increment 2). Remember: the view is y-inverted,
    // so +y points downward (toward the bottom of the screen) = gravity direction.
    constexpr float BARREL_RADIUS = 12.f;     // px
    constexpr float ROLL_SPEED = 160.f;       // px/sec, constant horizontal roll on a girder
    constexpr float GRAVITY = 900.f;          // px/sec^2, applied while falling
    constexpr float GIRDER_THICKNESS = 20.f;  // px
    constexpr float SEAM_SNAP_DISTANCE = 5.f;  // px, distance to snap to a girder when falling onto it

    constexpr float PLAYER_WIDTH = 20.f;        // px
    constexpr float PLAYER_HEIGHT = 32.f;       // px
    constexpr float PLAYER_JUMP_SPEED = 300.f;  // px/sec, initial jump
    constexpr float PLAYER_WALKING_SPEED = 120.f;  // px/sec, horizontal speed while on a girder
    constexpr float PLAYER_CLIMBING_SPEED = 100.f; // px/sec, vertical speed while climbing a ladder
    constexpr float PLAYER_MAX_FALL_HEIGHT = 80.f;  // px, maximum height the player can fall before dying

    constexpr float HAMMER_WIDTH = 16.f;
    constexpr float HAMMER_HEIGHT = 20.f;
    constexpr float HAMMER_DURATION = 10.f;
    constexpr float HAMMER_SWING_ANIMATION_INTERVAL = 0.2f;
    constexpr unsigned int HAMMER_BARREL_SCORE = 300u;

    constexpr float PLATFORM_MINIMUM_SNAP_DISTANCE = 2.f;  // px, minimum distance to snap to a platform when falling onto it

    constexpr float LADDER_WIDTH = 10.f;  // px

    constexpr unsigned int INITIAL_LIVES = 3;  // starting lives for the player
    constexpr float PLAYER_DEATH_DURATION = 3.f;  // seconds until the player is considered dead after dying

    constexpr float PLAYER_WALKING_ANIMATION_INTERVAL = 0.1f;  // seconds between walking animation frames
    constexpr float PLAYER_CLIMBING_ANIMATION_INTERVAL = 0.2f;  // seconds between climbing animation frames
    constexpr float BARREL_PLATFORM_ROLL_DISTANCE_FACTOR = 0.05f;
    constexpr float BARREL_CLIMBABLE_ROLL_DISTANCE_FACTOR = 0.1f;

    constexpr float DISSOLVING_PLATFORM_DISSOLVE_DURATION = 0.5f;  // seconds until the platform fully dissolves
    constexpr float DISSOLVING_PLATFORM_FALL_THROUGH_DURATION = 5.f;  // duration of the fall through in seconds
    constexpr float DISSOLVING_PLATFORM_DISSOLVE_H_TOLERANCE = 5.f; // px, inwards horizontal tolerance for the player to be considered on the platform for dissolving
    constexpr float DISSOLVING_PLATFORM_FALL_THROUGH_H_TOLERANCE = 0.f; // px, inwards horizontal tolerance for the player to be considered on the platform for fall-through
}

#endif
