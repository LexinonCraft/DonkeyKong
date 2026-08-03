#include "Game.hpp"

#include <SFML/Window/Keyboard.hpp>

#include "../model/Constants.hpp"

Game::Game() :
    window(sf::VideoMode({constants::VIEW_WIDTH, constants::VIEW_HEIGHT}), "Donkey Kong"),
    view(sf::FloatRect(sf::Vector2f({0,-constants::VIEW_HEIGHT}), sf::Vector2f({constants::VIEW_WIDTH,constants::VIEW_HEIGHT}))),
    game_layer(window),
    girders(),
    ladders(),
    barrel_control(game_layer),
    player_control(game_layer) {
        girders = build_girders();
        barrel_control.spawn(girders);
    
        // limit frame rate
        window.setFramerateLimit(constants::FRAME_RATE);

        // set the view (visible area) for our game
        game_layer.set_view(view);
}

std::vector<Girder> Game::build_girders() {
    // four girders alternating downhill direction so the barrel zig-zags down.
    // Remember: the view is y-inverted (+y = downward), so a larger y means lower on screen.
    std::vector<Girder> girders;
    girders.emplace_back(sf::Vector2f{120, -500}, sf::Vector2f{500, -460});
    girders.emplace_back(sf::Vector2f{80, -360},  sf::Vector2f{540, -400});
    girders.emplace_back(sf::Vector2f{40, -300},  sf::Vector2f{520, -260});
    girders.emplace_back(sf::Vector2f{80, -160},  sf::Vector2f{560, -200});
    return girders;
}

void Game::start() {
    // The clock is needed to control the speed of movement
    sf::Clock clock;

    while (window.isOpen()) {
        // Restart the clock and save the elapsed time into elapsed_time
        sf::Time elapsed_time = clock.restart();
 
        // handle input, check if window is still open
        if (!input()) {
            // update the scene according to the passed time
            update(elapsed_time.asSeconds());
            // draw the scene
            draw();
        }
    }
}

// returns true, if the window has been closed
bool Game::input() {
    while (std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            // quit
            window.close();
            return true;
        }
        // TODO: Process other events
        // examples:
        //if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            //if (keyPressed->code == sf::Keyboard::Key::Right) { // right arrow key pressed
                // ...
        // if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
            // if (keyReleased->code == sf::Keyboard::Key::Right) { // right arrow released
                // ...

        if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Up) {
                player_control.start_climbing_up();
                player_control.jump();
            } else if (keyPressed->code == sf::Keyboard::Key::Down) {
                player_control.start_climbing_down();
            }
        }
    }

    // handle continuous key presses (for smooth movement)
    bool leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    bool rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    if (leftPressed) {
        if (rightPressed) {
            player_control.set_horizontal_direction(Player::HorizontalDirection::None);
        } else {
            player_control.set_horizontal_direction(Player::HorizontalDirection::Left);
        }
    } else {
        if (rightPressed) {
            player_control.set_horizontal_direction(Player::HorizontalDirection::Right);
        } else {
            player_control.set_horizontal_direction(Player::HorizontalDirection::None);
        }
    }

    return false;
}

void Game::update(float time_passed) {
    barrel_control.update(time_passed, girders);
    player_control.update(time_passed, girders, ladders);
}

void Game::draw() {
    window.clear();

    game_layer.clear();
    // the stage is owned by Game, so Game draws it; the barrel goes on top
    for (const Girder& girder : girders) {
        game_layer.add_to_layer(girder.get_shape());
    }
    barrel_control.draw();
    player_control.draw();
    game_layer.draw();

    window.display();
}
