#ifndef TEST_STAGE_HPP
#define TEST_STAGE_HPP

#include <memory>

#include "DK/model/Stage.hpp"

class TestStageExitAnimation : public AbstractAnimation {
public:
    TestStageExitAnimation(Stage &stage) : AbstractAnimation(stage) {}
    void accept(AnimationVisitor &visitor) override {}
    bool is_finished() override { return true; }
    bool is_exit_animation() const override { return true; }
};

/**
 * @brief Stage used for testing
 */
class TestStage : public Stage {
public:
    TestStage(int rng(), PlayerData &player_data);

    void on_completed() override {}

    void spawn_lower_barrel();

    void spawn_upper_barrel();

    void place_hammer();

    void add_ladder();

    void start_exit_animation() { current_animation = std::make_unique<TestStageExitAnimation>(*this); }

    std::shared_ptr<Barrel> get_barrel() const { return barrel; }

    std::shared_ptr<Girder> get_lower_girder() const { return lower_girder; }
    std::shared_ptr<Girder> get_upper_girder() const { return upper_girder; }

    std::shared_ptr<Ladder> get_ladder() const { return ladder; }

    // Make barrels always roll down climbables for deterministic testing of barrel behavior.
    bool barrels_always_roll_down_climbables() const override { return true; }

private:
    std::shared_ptr<Barrel> barrel;
    std::shared_ptr<Girder> lower_girder;
    std::shared_ptr<Girder> upper_girder;
    std::shared_ptr<Ladder> ladder;
};

#endif
