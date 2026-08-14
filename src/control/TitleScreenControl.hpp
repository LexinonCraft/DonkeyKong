#ifndef TITLE_SCREEN_CONTROL_HPP
#define TITLE_SCREEN_CONTROL_HPP

#include "AbstractSceneControl.hpp"
#include "../view/TitleScreenView.hpp"

class TitleScreenControl : public AbstractSceneControl {
public:
    TitleScreenControl(sf::RenderWindow &window) : AbstractSceneControl(window), title_screen_view(window) {
        title_screen_view.set_view(view);
    }

    bool handle_input() override;

    void update(float dt) override;

    void draw() override;

    NextScene get_next_scene() const override;

private:
    TitleScreenView title_screen_view;
    NextScene next_scene = NextScene::Stay;
};

#endif
