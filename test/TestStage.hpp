#ifndef TEST_STAGE_HPP
#define TEST_STAGE_HPP

#include <memory>

#include "DK/model/Stage.hpp"

class TestStage : public Stage {
public:
    TestStage(int rng(), PlayerData &player_data);

    void on_completed() override {}

    void place_hammer();

    std::shared_ptr<Barrel> get_barrel() const { return barrel; }

    std::shared_ptr<Girder> get_girder() const { return girder; }

private:
    std::shared_ptr<Barrel> barrel;
    std::shared_ptr<Girder> girder;
};

#endif
