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

class TestStage : public Stage {
public:
    TestStage(int rng(), PlayerData &player_data);

    void on_completed() override {}

    void spawn_barrel();

    void place_hammer();

    void start_exit_animation() { current_animation = std::make_unique<TestStageExitAnimation>(*this); }

    std::shared_ptr<Barrel> get_barrel() const { return barrel; }

    std::shared_ptr<Girder> get_girder() const { return girder; }

private:
    std::shared_ptr<Barrel> barrel;
    std::shared_ptr<Girder> girder;
};

#endif
