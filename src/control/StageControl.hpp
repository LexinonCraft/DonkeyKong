#ifndef STAGE_CONTROL_HPP
#define STAGE_CONTROL_HPP

#include <cstdlib>
#include <memory>

#include "DK/control/AbstractSceneControl.hpp"
#include "DK/model/Stage.hpp"
#include "DK/view/StageView.hpp"
#include "DK/model/StageSequence.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/model/PlayerData.hpp"

class StageControl : public AbstractSceneControl {
public:
    StageControl(sf::RenderWindow &window, PlayerData &player_data, AssetsManager &assets_manager)
        : AbstractSceneControl(window), stage(create_stage(std::rand, player_data)), stage_view(window, *stage.get(), assets_manager) {}

    virtual ~StageControl() {}

    void handle_event(sf::Event *event) override;

    void handle_input() override;

    void update(float dt) override;

    void draw() override;

    NextScene get_next_scene() const override;

private:
    std::unique_ptr<Stage> stage;
    StageView stage_view;
    bool left_pressed = false;
    bool right_pressed = false;
    bool up_pressed = false;
    bool down_pressed = false;
};

#endif
