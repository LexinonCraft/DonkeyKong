#ifndef DEMO_STAGE_HPP
#define DEMO_STAGE_HPP

#include "Stage.hpp"
#include "Declarations.hpp"

/**
 * @brief Concrete test level used for the current prototype.
 *
 * This level constructs a small set of girders and ladders and places the game
 * objects needed to exercise the movement and climbing logic.
 */
class DemoStage : public Stage {
public:
    /**
     * @brief Creates the demo scene for the level.
     * @param id_generator Function used to allocate entity ids.
     */
    DemoStage(Id id_generator(), PlayerData &player_data);

    void update(float dt) override;

private:
    float time_since_last_spawn = 0.f;
};

#endif
