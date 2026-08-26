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
constexpr float MAX_DT = 0.05f;

constexpr const char *TEXTURES_BASE_PATH = "assets/textures/";
constexpr const char *FONT_FILE = "assets/fonts/PressStart2P.ttf";
constexpr const char *CONTRIBUTORS_FILE = "assets/contributors.txt";
constexpr const char *FALLBACK_CONTRIBUTORS_TEXT = "By Muvels and Lexinon";

constexpr float HALF_TURN_DEGREES = 180.f;
constexpr float NORMALIZED_CENTER = 0.5f;
constexpr float QUARTER_TURN_DEGREES = 90.f;
constexpr unsigned int TEXT_CHARACTER_SIZE = 24;

constexpr float GRAVITY = 900.f;
constexpr float PLATFORM_MINIMUM_SNAP_DISTANCE = 2.f;
constexpr float PLATFORM_UNDERNEATH_OFFSET = 0.1f;

constexpr float GIRDER_HORIZONTAL_SLOPE_TOLERANCE = 1e-6f;
constexpr float GIRDER_RENDER_TILE_WIDTH_FACTOR = 2.f;
constexpr float GIRDER_THICKNESS = 20.f;
constexpr float SEAM_SNAP_DISTANCE = 5.f;

constexpr float LADDER_BROKEN_GAP_HALF_HEIGHT = 10.f;
constexpr float LADDER_END_OVERHANG = 5.f;
constexpr float LADDER_TILE_HEIGHT = 20.f;
constexpr float LADDER_TILE_WIDTH = 20.f;

constexpr float BEAM_WIDTH = 3.f;

constexpr unsigned int INITIAL_LIVES = 3;
constexpr float PLAYER_WIDTH = 20.f;
constexpr float PLAYER_HEIGHT = 32.f;
constexpr float PLAYER_JUMP_SPEED = 300.f;
constexpr float PLAYER_WALKING_SPEED = 120.f;
constexpr float PLAYER_CLIMBING_SPEED = 100.f;
constexpr float PLAYER_MAX_FALL_HEIGHT = 80.f;
constexpr float PLAYER_DEATH_DURATION = 4.f;
constexpr float PLAYER_WALKING_ANIMATION_INTERVAL = 0.1f;
constexpr float PLAYER_CLIMBING_ANIMATION_INTERVAL = 0.2f;
constexpr float PLAYER_DYING_ANIMATION_INTERVAL = 0.075f;
constexpr float PLAYER_DYING_ANIMATION_TIME_BEFORE_ROTATION = 0.5f;
constexpr float PLAYER_DYING_ANIMATION_ROTATION_LENGTH = 1.2f;
constexpr unsigned int PLAYER_DYING_ANIMATION_FRAME_COUNT = 4;
constexpr unsigned int PLAYER_DEBUG_COLOR_RED = 200;
constexpr unsigned int PLAYER_DEBUG_COLOR_GREEN = 100;
constexpr unsigned int PLAYER_DEBUG_COLOR_BLUE = 100;
constexpr float PLAYER_HAMMER_SPRITE_ORIGIN_DIVISOR = 4.f;
constexpr float PLAYER_RENDER_SCALE = 2.f;

constexpr float HAMMER_WIDTH = 16.f;
constexpr float HAMMER_HEIGHT = 20.f;
constexpr float HAMMER_DURATION = 10.f;
constexpr float HAMMER_SWING_ANIMATION_INTERVAL = 0.2f;
constexpr float HAMMER_Y_OFFSET = 50.f;
constexpr unsigned int HAMMER_BARREL_SCORE = 300u;
constexpr unsigned int HAMMER_GHOST_SCORE = 500u;
constexpr unsigned int HAMMER_DEBUG_COLOR_RED = 240;
constexpr unsigned int HAMMER_DEBUG_COLOR_GREEN = 200;
constexpr unsigned int HAMMER_DEBUG_COLOR_BLUE = 60;
constexpr float HAMMER_RENDER_SIZE = 32.f;

constexpr float BARREL_RADIUS = 12.f;
constexpr float BARREL_HITBOX_RADIUS = 10.f;
constexpr float ROLL_SPEED = 130.f;
constexpr float BARREL_DIFFICULTY_INCREASE_PER_LEVEL = 0.1f;
constexpr float BARREL_MAX_DIFFICULTY_MULTIPLIER = 2.f;
constexpr float BARREL_LADDER_DESCENT_BASE_CHANCE = 50.f;
constexpr float BARREL_LADDER_DESCENT_MAX_CHANCE = 90.f;
constexpr float BARREL_LADDER_DESCENT_DISTANCE_PER_PERCENT = 10.f;
constexpr int BARREL_LADDER_DESCENT_CHANCE_STEPS = 100;
constexpr float BARREL_PLATFORM_ROLL_DISTANCE_FACTOR = 0.05f;
constexpr float BARREL_CLIMBABLE_ROLL_DISTANCE_FACTOR = 0.1f;
constexpr float BARREL_JUMP_MAX_Y_DIFF = 30.f;
constexpr unsigned int BARREL_JUMP_SCORE = 100;
constexpr unsigned int BARREL_DEBUG_COLOR_RED = 120;
constexpr unsigned int BARREL_DEBUG_COLOR_GREEN = 200;
constexpr unsigned int BARREL_DEBUG_COLOR_BLUE = 230;
constexpr float BARREL_RENDER_SIZE_FACTOR = 2.5f;
constexpr float BARREL_RENDER_VERTICAL_OFFSET_FACTOR = 5.f / 16.f;
constexpr float BARREL_STACK_ROTATION = QUARTER_TURN_DEGREES;
constexpr unsigned int BARREL_FRONT_ANIMATION_FRAME_COUNT = 4;

constexpr float BARREL_THROW_ANIMATION_INTERVAL = 0.5f;
constexpr float BARREL_THROW_OFFSET_X = 20.f;
constexpr unsigned int MAX_BARRELS_THROWN = 4;
constexpr float DONKEY_KONG_MIN_IDLE_DURATION = 1.f;
constexpr float DONKEY_KONG_MAX_IDLE_DURATION = 3.f;
constexpr unsigned int DONKEY_KONG_IDLE_DURATION_STEPS = 5;
constexpr float DONKEY_KONG_ANGRY_ANIMATION_INTERVAL = 0.75f;
constexpr unsigned int DONKEY_KONG_MIN_ANGRY_ANIMATION_FRAMES = 2;
constexpr unsigned int DONKEY_KONG_MAX_ANGRY_ANIMATION_FRAMES = 5;
constexpr unsigned int DONKEY_KONG_MAX_CONSECUTIVE_ANGRY_ACTIONS = 1;
constexpr unsigned int DONKEY_KONG_ACTION_COUNT = 3;
constexpr unsigned int DONKEY_KONG_THROW_BARREL_FRAME = 2;
constexpr unsigned int DONKEY_KONG_THROW_ANIMATION_FRAME_COUNT = 4;
constexpr unsigned int DONKEY_KONG_AFTER_FALL_ANIMATION_FRAME_COUNT = 3;
constexpr float DONKEY_KONG_BEFORE_FALL_FRAME_INTERVAL = 0.2f;
constexpr float DONKEY_KONG_AFTER_FALL_FRAME_INTERVAL = 0.15f;
constexpr float DONKEY_KONG_HOLDED_BARREL_OFFSET_Y = 10.f;
constexpr float DONKEY_KONG_HITBOX_WIDTH = 64.f;
constexpr float DONKEY_KONG_HITBOX_HEIGHT = 64.f;
constexpr float DONKEY_KONG_CLIMBING_FRAME_INTERVAL = 0.25f;
constexpr float DONKEY_KONG_RENDER_SCALE = 2.f;

constexpr float PAULINE_ANIMATION_LENGTH = 7.f;
constexpr float PAULINE_SCREAM_ANIMATION_INTERVAL = 0.15f;
constexpr unsigned int PAULINE_SCREAM_ANIMATION_FRAMES = 9;
constexpr float PAULINE_FALL_VERTICAL_OFFSET_FACTOR = 5.f / 32.f;
constexpr float PAULINE_HELP_OFFSET = 40.f;
constexpr float PAULINE_HEART_OFFSET_Y = 40.f;
constexpr float PAULINE_RENDER_SCALE = 2.f;

constexpr float GHOST_WIDTH = 32.f;
constexpr float GHOST_HEIGHT = 32.f;
constexpr float GHOST_MINIMUM_MOVING_DURATION = 5.f;
constexpr float GHOST_MAXIMUM_MOVING_DURATION = 12.f;
constexpr unsigned int GHOST_MOVING_DURATION_STEPS = 8;
constexpr float GHOST_MINIMUM_IDLE_DURATION = 1.f;
constexpr float GHOST_MAXIMUM_IDLE_DURATION = 4.f;
constexpr unsigned int GHOST_IDLE_DURATION_STEPS = 5;
constexpr float GHOST_MOVING_SPEED = 60.f;
constexpr float GHOST_LIFT = 5.f;
constexpr float GHOST_ANIMATION_INTERVAL = 0.3f;
constexpr float GHOST_COLLISION_WIDTH_DIVISOR = 8.f;
constexpr unsigned int GHOST_CLIMB_CHANCE_STEPS = 3;
constexpr float GHOST_HITBOX_HEIGHT_FACTOR = 0.75f;
constexpr float GHOST_RENDER_SCALE = 2.f;
constexpr unsigned int GHOST_ANIMATION_FRAME_COUNT = 2;
constexpr float GHOST_SPAWN_INTERVAL = 10.f;
constexpr unsigned int GHOST_SPAWN_X_POS_STEPS = 1024;
constexpr float GHOST_SPAWN_MIN_DISTANCE = 200.f;

constexpr float DISSOLVING_PLATFORM_DISSOLVE_DURATION = 0.5f;
constexpr float DISSOLVING_PLATFORM_DISSOLVE_H_TOLERANCE = 5.f;
constexpr float DISSOLVING_PLATFORM_FALL_THROUGH_H_TOLERANCE = 0.f;
constexpr unsigned int DISSOLVING_PLATFORM_SCORE = 300;

constexpr float SCORE_EFFECT_RISE_SPEED = 50.f;
constexpr float SCORE_EFFECT_DURATION = 1.f;
constexpr unsigned int SCORE_EFFECT_CHARACTER_SIZE = 12;

constexpr float TITLE_SCREEN_ANIMATION_LENGTH = 5.f;
constexpr unsigned int TITLE_SCREEN_ANGRY_FRAME_COUNT = 3;
constexpr unsigned int TITLE_SCREEN_TITLE_CHARACTER_SIZE = 48;
constexpr unsigned int TITLE_SCREEN_CONTRIBUTORS_CHARACTER_SIZE = 6;
constexpr float TITLE_SCREEN_TITLE_Y = -100.f;
constexpr float TITLE_SCREEN_START_TEXT_Y = 100.f;
constexpr float TITLE_SCREEN_DONKEY_KONG_SCALE = 3.f;
constexpr float TITLE_SCREEN_CONTRIBUTORS_Y = -50.f;
constexpr float TITLE_SCREEN_HIGHSCORE_LABEL_Y = 50.f;
constexpr float TITLE_SCREEN_HIGHSCORE_Y = 74.f;

constexpr float GAME_OVER_DURATION = 7.f;
constexpr unsigned int GAME_OVER_TITLE_CHARACTER_SIZE = 60;
constexpr float GAME_OVER_TITLE_Y = -50.f;
constexpr float GAME_OVER_SCORE_Y = 50.f;

constexpr float STAGE_TRANSITION_DURATION = 5.f;
constexpr unsigned int STAGE_TRANSITION_STAGE_CHARACTER_SIZE = 18;
constexpr float STAGE_TRANSITION_QUESTION_Y = -50.f;
constexpr float STAGE_TRANSITION_ROW_START_Y = -150.f;
constexpr float STAGE_TRANSITION_ROW_SPACING = 100.f;
constexpr float STAGE_TRANSITION_DONKEY_KONG_SCALE = 0.7f;
constexpr float STAGE_TRANSITION_STAGE_TEXT_X = -150.f;

constexpr float STAGE_HUD_SCORE_X = 70.f;
constexpr float STAGE_HUD_TEXT_ROW_HEIGHT = 24.f;
constexpr float STAGE_HUD_ICON_X = 30.f;
constexpr float STAGE_HUD_COUNT_X = 50.f;
constexpr float STAGE_HUD_HAMMER_ICON_Y = 104.f;
constexpr float STAGE_HUD_HAMMER_COUNT_Y = 110.f;
constexpr float STAGE_HUD_BARREL_Y = 140.f;
constexpr float STAGE_HUD_LIFE_START_X = 30.f;
constexpr float STAGE_HUD_LIFE_SPACING = 30.f;
constexpr float STAGE_HUD_LIFE_Y = 80.f;
constexpr float STAGE_HUD_LEVEL_X = -100.f;
constexpr float STAGE_HUD_LEVEL_Y = 100.f;
constexpr float STAGE_HUD_SPRITE_SCALE = 2.f;

constexpr float STAGE_25M_UNITED_DURATION = 3.f;
constexpr float STAGE_25M_COMPLETION_DURATION = 5.f;
constexpr float STAGE_25M_COMPLETION_DONKEY_KONG_X = 205.f;
constexpr float STAGE_25M_COMPLETION_DONKEY_KONG_Y = -550.f;
constexpr float STAGE_25M_COMPLETION_CLIMBING_SPEED = 75.f;

constexpr float STAGE_100M_BEFORE_FALL_DURATION = 1.5f;
constexpr float STAGE_100M_FALLING_SPEED = 200.f;
constexpr float STAGE_100M_IMPACT_Y = -100.f;
constexpr float STAGE_100M_IMPACT_DURATION = 2.5f;
constexpr float STAGE_100M_FINAL_PLATFORM_Y = -430.f;
constexpr float STAGE_100M_FINAL_PAULINE_X = 200.f;
constexpr float STAGE_100M_FINAL_PLAYER_RIGHT_MARGIN = 200.f;
constexpr float STAGE_100M_UNITED_DURATION = 5.f;
constexpr float STAGE_100M_HIDDEN_GIRDER_Y = 100.f;
constexpr unsigned int STAGE_100M_LOWER_GIRDER_HIDE_OFFSET = 2;
constexpr unsigned int STAGE_100M_INITIAL_GHOST_COUNT = 4;
constexpr unsigned int STAGE_100M_MAX_GHOST_COUNT = 8;
} // namespace constants

#endif
