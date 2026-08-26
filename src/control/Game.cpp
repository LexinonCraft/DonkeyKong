#include "DK/control/Game.hpp"

#include <algorithm>

#include "DK/Constants.hpp"
#include "DK/control/GameOverControl.hpp"
#include "DK/control/StageControl.hpp"
#include "DK/control/StageTransitionControl.hpp"
#include "DK/control/TitleScreenControl.hpp"

Game::Game()
    : window(sf::VideoMode({constants::VIEW_WIDTH, constants::VIEW_HEIGHT}), "Donkey Kong"), assets_manager(),
      scene_control(std::unique_ptr<AbstractSceneControl>(new TitleScreenControl(window, assets_manager, player_data))) {
    // limit frame rate
    window.setFramerateLimit(constants::FRAME_RATE);

    // set icon
    auto image = sf::Image();
    if (!image.loadFromFile("assets/icon.png")) {
        throw std::runtime_error("Failed to load icon");
    }
    window.setIcon(image.getSize(), image.getPixelsPtr());
}

void Game::run() {
    // The clock is needed to control the speed of movement
    sf::Clock clock;

    while (window.isOpen()) {
        // Restart the clock and save the elapsed time into elapsed_time
        sf::Time elapsed_time = clock.restart();

        // handle input, check if window is still open
        if (!input()) {
            float dt = std::min(elapsed_time.asSeconds(), constants::MAX_DT);
            // update the scene according to the passed time
            scene_control->update(dt);
            // draw the scene
            scene_control->draw();

            // check if we need to switch to a different scene
            handle_next_scene(scene_control->get_next_scene());
        }
    }
}

bool Game::input() {
    while (std::optional<sf::Event> event = window.pollEvent()) {
        // check if the window was closed
        if (event->is<sf::Event::Closed>()) {
            // quit
            window.close();
            return true;
        }

        // dispatch the event to the scene control
        scene_control->handle_event(&(*event));
    }

    // let the scene control handle continuous input (e.g. holding down a key)
    scene_control->handle_input();

    return false;
}

void Game::handle_next_scene(AbstractSceneControl::NextScene next_scene) {
    switch (next_scene) {
        case AbstractSceneControl::NextScene::Stay:
            break;
        case AbstractSceneControl::NextScene::TitleScreen:
            scene_control = std::unique_ptr<AbstractSceneControl>(new TitleScreenControl(window, assets_manager, player_data));
            break;
        case AbstractSceneControl::NextScene::StageTransition:
            scene_control = std::unique_ptr<AbstractSceneControl>(new StageTransitionControl(window, player_data, assets_manager));
            break;
        case AbstractSceneControl::NextScene::Stage:
            scene_control = std::unique_ptr<AbstractSceneControl>(new StageControl(window, player_data, assets_manager));
            break;
        case AbstractSceneControl::NextScene::GameOver:
            scene_control = std::unique_ptr<AbstractSceneControl>(new GameOverControl(window, player_data, assets_manager));
            break;
    }
}
