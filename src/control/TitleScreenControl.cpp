#include "TitleScreenControl.hpp"

void TitleScreenControl::handle_event(sf::Event *event) {
    if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Enter) {
            next_scene = NextScene::StageTransition; // Transition to the stage scene
        }
    }
}

void TitleScreenControl::handle_input() {
    // No continuous input handling for the title screen
}

void TitleScreenControl::update(float dt) {
    // No update logic for the title screen
}

void TitleScreenControl::draw() {
    title_screen_view.draw();
}

AbstractSceneControl::NextScene TitleScreenControl::get_next_scene() const {
    return next_scene;
}
