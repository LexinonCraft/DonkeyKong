#include "DK/control/TitleScreenControl.hpp"

void TitleScreenControl::handle_event(sf::Event *event) {
    if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Enter) {
            next_scene = NextScene::StageTransition; // Transition to the stage scene
        }
    }
}
