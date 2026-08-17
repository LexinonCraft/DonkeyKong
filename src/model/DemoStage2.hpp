#ifndef DEMO_STAGE2_HPP
#define DEMO_STAGE2_HPP

#include "Stage.hpp"
#include "Declarations.hpp"

/**
 * @brief Concrete test level used for the current prototype.
 *
 * This level constructs a small set of girders and ladders and places the game
 * objects needed to exercise the movement and climbing logic.
 */
class DemoStage2 : public Stage {
public:
    /**
     * @brief Creates the demo scene for the level.
     * @param id_generator Function used to allocate entity ids.
     */
    DemoStage2(Id id_generator(), PlayerData &player_data);

private:
    float time_since_last_spawn = 0.f;

    void update_while_running(float dt) override;
};

#endif
