#ifndef TITLE_SCREEN_CONTROL_HPP
#define TITLE_SCREEN_CONTROL_HPP

#include "DK/control/AbstractSceneControl.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/TitleScreenView.hpp"

class TitleScreenControl : public AbstractSceneControl {
public:
    TitleScreenControl(sf::RenderWindow &window, AssetsManager &assets_manager, PlayerData &player_data) : AbstractSceneControl(window), title_screen_view(window, assets_manager, player_data) {}

    void handle_event(sf::Event *event) override;

    void handle_input() override;

    void update(float dt) override;

    void draw() override;

    NextScene get_next_scene() const override;

private:
    TitleScreenView title_screen_view;
    NextScene next_scene = NextScene::Stay;
    float animation_timer = 0.0f;
};

#endif
