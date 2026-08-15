#include "Game.hpp"

#include <SFML/Window/Keyboard.hpp>

#include "../model/Constants.hpp"
#include "StageControl.hpp"
#include "TitleScreenControl.hpp"

Game::Game() :
    window(sf::VideoMode({constants::VIEW_WIDTH, constants::VIEW_HEIGHT}), "Donkey Kong"), assets_manager("assets/textures/", "assets/fonts/PressStart2P.ttf"), scene_control(std::unique_ptr<AbstractSceneControl>(new TitleScreenControl(window, assets_manager))) {
        // limit frame rate
        window.setFramerateLimit(constants::FRAME_RATE);

        // set icon
        auto image = sf::Image();
        if (!image.loadFromFile("assets/icon.png")) {
            throw std::runtime_error("Failed to load icon");
        }
        window.setIcon(image.getSize(), image.getPixelsPtr());

        // level->set_player(std::rand, &player_control.get_player());
}

void Game::run() {
    // The clock is needed to control the speed of movement
    sf::Clock clock;

    while (window.isOpen()) {
        // Restart the clock and save the elapsed time into elapsed_time
        sf::Time elapsed_time = clock.restart();
 
        // handle input, check if window is still open
        if (!input()) {
            // update the scene according to the passed time
            scene_control->update(elapsed_time.asSeconds());
            // draw the scene
            scene_control->draw();

            // check if we need to switch to a different scene
            handle_next_scene(scene_control->get_next_scene());
        }
    }
}

bool Game::input() {
    while (std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            // quit
            window.close();
            return true;
        }

        scene_control->handle_event(&(*event));
    }

    scene_control->handle_input();

    return false;
}

void Game::handle_next_scene(AbstractSceneControl::NextScene next_scene) {
    switch (next_scene) {
        case AbstractSceneControl::NextScene::Stay:
            break;
        case AbstractSceneControl::NextScene::MainMenu:
            scene_control = std::unique_ptr<AbstractSceneControl>(new TitleScreenControl(window, assets_manager));
            break;
        case AbstractSceneControl::NextScene::Stage:
            scene_control = std::unique_ptr<AbstractSceneControl>(new StageControl(window, player_data, assets_manager));
            break;
    }
}
