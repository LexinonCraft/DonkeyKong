#ifndef STAGE_CONTROL_HPP
#define STAGE_CONTROL_HPP

#include <cstdlib>
#include <memory>

#include "AbstractSceneControl.hpp"
#include "../model/Stage.hpp"
#include "../view/StageView.hpp"
#include "../model/StageSequence.hpp"
#include "../view/AssetsManager.hpp"
#include "../model/PlayerData.hpp"

class StageControl : public AbstractSceneControl {
public:
    StageControl(sf::RenderWindow &window, PlayerData &player_data, AssetsManager &assets_manager)
        : AbstractSceneControl(window), stage(create_stage(std::rand, player_data)), stage_view(window, *stage.get(), assets_manager), player_data(player_data) {}

    virtual ~StageControl() {}

    void handle_event(sf::Event *event) override;

    void handle_input() override;

    void update(float dt) override;

    void draw() override;

    NextScene get_next_scene() const override;

private:
    std::unique_ptr<Stage> stage;
    StageView stage_view;
    PlayerData &player_data;
};

#endif
