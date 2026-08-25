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
constexpr float BARREL_RADIUS = 12.f; // px
constexpr float BARREL_HITBOX_RADIUS = 10.f;
constexpr float ROLL_SPEED = 130.f; // px/sec, constant horizontal roll on a girder
constexpr float BARREL_DIFFICULTY_INCREASE_PER_LEVEL = 0.1f;
constexpr float BARREL_MAX_DIFFICULTY_MULTIPLIER = 2.f;
constexpr float BARREL_LADDER_DESCENT_BASE_CHANCE = 50.f;
constexpr float BARREL_LADDER_DESCENT_MAX_CHANCE = 90.f;
constexpr float BARREL_LADDER_DESCENT_DISTANCE_PER_PERCENT = 10.f;
constexpr int BARREL_LADDER_DESCENT_CHANCE_STEPS = 100;
constexpr float GRAVITY = 900.f;          // px/sec^2, applied while falling
constexpr float GIRDER_THICKNESS = 20.f;  // px
constexpr float SEAM_SNAP_DISTANCE = 5.f; // px, distance to snap to a girder when falling onto it

constexpr float PLAYER_WIDTH = 20.f;           // px
constexpr float PLAYER_HEIGHT = 32.f;          // px
constexpr float PLAYER_JUMP_SPEED = 300.f;     // px/sec, initial jump
constexpr float PLAYER_WALKING_SPEED = 120.f;  // px/sec, horizontal speed while on a girder
constexpr float PLAYER_CLIMBING_SPEED = 100.f; // px/sec, vertical speed while climbing a ladder
constexpr float PLAYER_MAX_FALL_HEIGHT = 80.f; // px, maximum height the player can fall before dying

constexpr float HAMMER_WIDTH = 16.f;
constexpr float HAMMER_HEIGHT = 20.f;
constexpr float HAMMER_DURATION = 10.f;
constexpr float HAMMER_SWING_ANIMATION_INTERVAL = 0.2f;
constexpr unsigned int HAMMER_BARREL_SCORE = 300u;
constexpr unsigned int HAMMER_GHOST_SCORE = 500u;

constexpr float PLATFORM_MINIMUM_SNAP_DISTANCE = 2.f; // px, minimum distance to snap to a platform when falling onto it

constexpr float LADDER_WIDTH = 10.f; // px

constexpr unsigned int INITIAL_LIVES = 3;    // starting lives for the player
constexpr float PLAYER_DEATH_DURATION = 4.f; // seconds until the player is considered dead after dying

constexpr float PLAYER_WALKING_ANIMATION_INTERVAL = 0.1f;  // seconds between walking animation frames
constexpr float PLAYER_CLIMBING_ANIMATION_INTERVAL = 0.2f; // seconds between climbing animation frames
constexpr float BARREL_PLATFORM_ROLL_DISTANCE_FACTOR = 0.05f;
constexpr float BARREL_CLIMBABLE_ROLL_DISTANCE_FACTOR = 0.1f;

constexpr float BARREL_THROW_ANIMATION_INTERVAL = 0.5f;       // seconds between barrel throwing animation frames
constexpr float BARREL_THROW_OFFSET_X = 20.f;                 // px, horizontal offset from Donkey Kong's position when throwing a barrel
constexpr unsigned int MAX_BARRELS_THROWN = 4;                // maximum number of barrels Donkey Kong can throw in one action
constexpr float DONKEY_KONG_MIN_IDLE_DURATION = 1.f;          // seconds, minimum duration Donkey Kong stays idle before taking an action
constexpr float DONKEY_KONG_MAX_IDLE_DURATION = 3.f;          // seconds, maximum duration Donkey Kong stays idle before taking an action
constexpr unsigned int DONKEY_KONG_IDLE_DURATION_STEPS = 5;   // number of discrete steps for idle duration randomization
constexpr float DONKEY_KONG_ANGRY_ANIMATION_INTERVAL = 0.75f; // seconds between angry animation frames
constexpr unsigned int DONKEY_KONG_MIN_ANGRY_ANIMATION_FRAMES = 2; // minimum number of angry animation frames before switching back to idle
constexpr unsigned int DONKEY_KONG_MAX_ANGRY_ANIMATION_FRAMES = 5; // maximum number of angry animation frames before switching back to idle
constexpr unsigned int DONKEY_KONG_MAX_CONSECUTIVE_ANGRY_ACTIONS =
    1;                                                     // maximum number of consecutive angry actions before forcing a barrel throw
constexpr float DONKEY_KONG_HOLDED_BARREL_OFFSET_Y = 10.f; // px, vertical offset from Donkey Kong's position when holding a barrel

constexpr float PAULINE_ANIMATION_LENGTH = 7.f;             // seconds, duration of Pauline's animation cycle
constexpr float PAULINE_SCREAM_ANIMATION_INTERVAL = 0.15f;  // seconds between Pauline's scream animation frames
constexpr unsigned int PAULINE_SCREAM_ANIMATION_FRAMES = 9; // number of frames in Pauline's scream animation

constexpr float DISSOLVING_PLATFORM_DISSOLVE_DURATION = 0.5f;    // seconds until the platform fully dissolves
constexpr float DISSOLVING_PLATFORM_FALL_THROUGH_DURATION = 5.f; // duration of the fall through in seconds
constexpr float DISSOLVING_PLATFORM_DISSOLVE_H_TOLERANCE =
    5.f; // px, inwards horizontal tolerance for the player to be considered on the platform for dissolving
constexpr float DISSOLVING_PLATFORM_FALL_THROUGH_H_TOLERANCE =
    0.f; // px, inwards horizontal tolerance for the player to be considered on the platform for fall-through

constexpr float TITLE_SCREEN_ANIMATION_LENGTH = 5.f; // length of the donkey kong animation on the title screen in seconds

constexpr float SCORE_EFFECT_RISE_SPEED = 50.f; // px/sec, speed at which the score effect rises
constexpr float SCORE_EFFECT_DURATION = 1.f;    // seconds, duration of the score effect

constexpr float BARREL_JUMP_MAX_Y_DIFF = 30.f; // px, maximum height of the player's feet above the barrel

constexpr unsigned int BARREL_JUMP_SCORE = 100; // points awarded for jumping over a barrel

constexpr float GHOST_WIDTH = 32.f;                     // px, width of the ghost entity
constexpr float GHOST_HEIGHT = 32.f;                    // px, height of the ghost entity
constexpr float GHOST_MINIMUM_MOVING_DURATION = 5.f;    // seconds, minimum duration the ghost moves on a platform before changing state
constexpr float GHOST_MAXIMUM_MOVING_DURATION = 12.f;   // seconds, maximum duration the ghost moves on a platform before changing state
constexpr unsigned int GHOST_MOVING_DURATION_STEPS = 8; // number of discrete steps for randomizing the ghost's moving duration
constexpr float GHOST_MINIMUM_IDLE_DURATION = 1.f;      // seconds, minimum duration the ghost idles on a platform before changing state
constexpr float GHOST_MAXIMUM_IDLE_DURATION = 4.f;      // seconds, maximum duration the ghost idles on a platform before changing state
constexpr unsigned int GHOST_IDLE_DURATION_STEPS = 5;   // number of discrete steps for randomizing the ghost's idle duration
constexpr float GHOST_MOVING_SPEED = 60.f;              // px/sec, speed at which the ghost moves on a platform
constexpr float GHOST_LIFT = 5.f;                       // px, how much the ghost levitates above the platform
constexpr float GHOST_ANIMATION_INTERVAL = 0.3f;        // seconds between ghost animation frames

constexpr float PLATFORM_UNDERNEATH_OFFSET = 0.1f;

constexpr float GHOST_SPAWN_INTERVAL = 10.f;                        // seconds between ghost spawns
constexpr unsigned int GHOST_SPAWN_X_POS_STEPS = 1024;              // number of discrete steps for randomizing the ghost's spawn x position
constexpr float GHOST_SPAWN_MIN_DISTANCE = 200.f;                   // px, minimum distance from the player for a ghost to spawn
constexpr unsigned int STAGE_100M_INITIAL_GHOST_COUNT = 4;          // number of ghosts to spawn at the beginning of the stage
constexpr unsigned int STAGE_100M_MAX_GHOST_COUNT = 8;              // maximum number of ghosts allowed in the stage at any given time
constexpr float PLAYER_DYING_ANIMATION_INTERVAL = 0.075f;           // seconds between dying animation frames
constexpr float PLAYER_DYING_ANIMATION_TIME_BEFORE_ROTATION = 0.5f; // seconds until the player starts rotating during the dying animation
constexpr float PLAYER_DYING_ANIMATION_ROTATION_LENGTH = 1.2f;      // duration of the rotation in seconds during the dying animation

constexpr float HEART_BREAKING_DURATION = 1.5f;          // seconds until the heart breaks after the stage is completed
constexpr float DONKEY_KONG_SHOW_TEETH_INTERVAL = 0.3f;  // seconds between Donkey Kong showing his teeth after the stage is completed
constexpr unsigned int DONKEY_KONG_SHOW_TEETH_TIMES = 3; // number of times Donkey Kong shows his teeth after the stage is completed
constexpr float DONKEY_KONG_JUMP_SPEED = 450.f;          // px/sec, initial jump speed for Donkey Kong after the stage is completed
constexpr float DONKEY_KONG_HITBOX_WIDTH = 64.f;         // px, width of Donkey Kong's hitbox
constexpr float DONKEY_KONG_HITBOX_HEIGHT = 64.f;        // px, height of Donkey Kong's hitbox

constexpr float DONKEY_KONG_CLIMBING_FRAME_INTERVAL = 0.25f; // seconds between Donkey Kong's climbing animation frames
constexpr float HAMMER_Y_OFFSET = 50.f;                      // px, vertical offset from the platform's surface to place the hammer power-up

constexpr unsigned int DISSOLVING_PLATFORM_SCORE = 300;
constexpr float DONKEY_KONG_BEFORE_FALL_FRAME_INTERVAL = 0.2f; // seconds between Donkey Kong's before falling animation frames
constexpr float DONKEY_KONG_AFTER_FALL_FRAME_INTERVAL = 0.15f; // seconds between Donkey Kong's after falling animation frames

constexpr float BEAM_WIDTH = 3.f; // px, width of the beam entity

constexpr const char *FALLBACK_CONTRIBUTORS_TEXT = "By Muvels and Lexinon";

constexpr const char *TEXTURES_BASE_PATH = "assets/textures/";
constexpr const char *FONT_FILE = "assets/fonts/PressStart2P.ttf";
constexpr const char *CONTRIBUTORS_FILE = "assets/contributors.txt";
} // namespace constants

#endif
