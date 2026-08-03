// define some constants to make code more readable
namespace constants {
    constexpr int VIEW_WIDTH = 600;
    constexpr int VIEW_HEIGHT = 600;
    constexpr unsigned int FRAME_RATE = 60;

    // barrel / girder physics (increment 2). Remember: the view is y-inverted,
    // so +y points downward (toward the bottom of the screen) = gravity direction.
    constexpr float BARREL_RADIUS = 12.f;     // px
    constexpr float ROLL_SPEED = 160.f;       // px/sec, constant horizontal roll on a girder
    constexpr float GRAVITY = 900.f;          // px/sec^2, applied while falling
    constexpr float GIRDER_THICKNESS = 12.f;  // px

    constexpr float PLAYER_WIDTH = 20.f;        // px
    constexpr float PLAYER_HEIGHT = 32.f;       // px
    constexpr float PLAYER_JUMP_SPEED = 400.f;  // px/sec, initial jump
    constexpr float PLAYER_WALKING_SPEED = 120.f;  // px/sec, horizontal speed while on a girder
}
