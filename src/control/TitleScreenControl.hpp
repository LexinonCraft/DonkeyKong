#ifndef TITLE_SCREEN_CONTROL_HPP
#define TITLE_SCREEN_CONTROL_HPP

#include "DK/control/AbstractSceneControl.hpp"
#include "DK/view/Declarations.hpp"
#include "DK/view/views/TitleScreenView.hpp"

/**
 * @brief Control class for the title screen.
 */
class TitleScreenControl : public AbstractSceneControl {
public:
    TitleScreenControl(sf::RenderWindow &window, AssetsManager &assets_manager, PlayerData &player_data)
        : AbstractSceneControl(window), title_screen_view(window, assets_manager, player_data) {}

    void handle_event(sf::Event *event) override;

    void handle_input() override {}

    void update(float dt) override { title_screen_view.update(dt); }

    void draw() override { title_screen_view.draw(); }

    NextScene get_next_scene() const override { return next_scene; }

private:
    TitleScreenView title_screen_view;
    NextScene next_scene = NextScene::Stay;
};

#endif
