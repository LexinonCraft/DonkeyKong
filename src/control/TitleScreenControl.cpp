#include "DK/control/TitleScreenControl.hpp"

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
    animation_timer += dt;
    if (animation_timer >= constants::TITLE_SCREEN_ANIMATION_LENGTH) {
        animation_timer -= constants::TITLE_SCREEN_ANIMATION_LENGTH;
    }
}

void TitleScreenControl::draw() { title_screen_view.draw(animation_timer); }

AbstractSceneControl::NextScene TitleScreenControl::get_next_scene() const { return next_scene; }
