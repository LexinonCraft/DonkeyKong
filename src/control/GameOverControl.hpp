#ifndef GAME_OVER_CONTROL_HPP
#define GAME_OVER_CONTROL_HPP

#include "DK/control/AbstractSceneControl.hpp"
#include "DK/model/PlayerData.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/views/GameOverView.hpp"

class GameOverControl : public AbstractSceneControl {
public:
    GameOverControl(sf::RenderWindow &window, PlayerData &player_data, AssetsManager &assets_manager)
        : AbstractSceneControl(window), game_over_view(window, assets_manager), player_data(player_data) {}

    void handle_event(sf::Event *event) override;

    void handle_input() override;

    void update(float dt) override;

    void draw() override;

    NextScene get_next_scene() const override;

private:
    GameOverView game_over_view;
    NextScene next_scene = NextScene::Stay;
    float time_elapsed = 0.f;
    PlayerData &player_data;
};

#endif
