#include "TitleScreenControl.hpp"

bool TitleScreenControl::handle_input() {
    while (std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            // quit
            window.close();
            return true;
        }
        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Enter) {
                next_scene = NextScene::Stage; // Transition to the stage scene
            }
        }
    }
    return false;
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
