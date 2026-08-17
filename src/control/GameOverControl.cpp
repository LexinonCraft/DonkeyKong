#include "GameOverControl.hpp"

void GameOverControl::handle_event(sf::Event *event) {
    // No event handling for the title screen
}

void GameOverControl::handle_input() {
    // No continuous input handling for the title screen
}

void GameOverControl::update(float dt) {
    time_elapsed += dt;
    if (time_elapsed >= 7.f) {
        player_data.reset();
        next_scene = NextScene::MainMenu;
    }
}

void GameOverControl::draw() {
    game_over_view.draw();
}

AbstractSceneControl::NextScene GameOverControl::get_next_scene() const {
    return next_scene;
}
