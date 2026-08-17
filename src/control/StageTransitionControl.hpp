#ifndef STAGE_TRANSITION_CONTROL_HPP
#define STAGE_TRANSITION_CONTROL_HPP

#include "AbstractSceneControl.hpp"
#include "../view/AssetsManager.hpp"
#include "../view/StageTransitionView.hpp"

class StageTransitionControl : public AbstractSceneControl {
public:
    StageTransitionControl(sf::RenderWindow &window, PlayerData &player_data, AssetsManager &assets_manager) 
        : AbstractSceneControl(window), stage_transition_view(window, assets_manager, player_data) {}

    void handle_event(sf::Event *event) override;

    void handle_input() override;

    void update(float dt) override;

    void draw() override;

    NextScene get_next_scene() const override;

private:
    StageTransitionView stage_transition_view;
    float time_elapsed = 0.f;
};

#endif
