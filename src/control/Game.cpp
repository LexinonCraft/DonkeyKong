#include "Game.hpp"

#include <memory>

#include <SFML/Window/Keyboard.hpp>

#include "../model/Constants.hpp"
#include "../model/DemoLevel.hpp"

Game::Game() :
    window(sf::VideoMode({constants::VIEW_WIDTH, constants::VIEW_HEIGHT}), "Donkey Kong"),
    level(new DemoLevel(std::rand)),
    view(sf::FloatRect(sf::Vector2f({0,-constants::VIEW_HEIGHT}), sf::Vector2f({constants::VIEW_WIDTH,constants::VIEW_HEIGHT}))),
    level_view(window, *level) {
        // limit frame rate
        window.setFramerateLimit(constants::FRAME_RATE);

        // set the view (visible area) for our game
        level_view.set_view(view);

        // level->set_player(std::rand, &player_control.get_player());
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
    std::shared_ptr<Player> player = level->get_player().lock();

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
            if (keyPressed->code == sf::Keyboard::Key::Space) {
                player->jump();
            }
        }
    }

    // handle continuous key presses (for smooth movement)
    bool leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    bool rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    if (leftPressed) {
        if (rightPressed) {
            player->set_horizontal_direction(Player::HorizontalDirection::None);
        } else {
            player->set_horizontal_direction(Player::HorizontalDirection::Left);
        }
    } else {
        if (rightPressed) {
            player->set_horizontal_direction(Player::HorizontalDirection::Right);
        } else {
            player->set_horizontal_direction(Player::HorizontalDirection::None);
        }
    }

    bool upPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    bool downPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
    if (upPressed) {
        if (downPressed) {
            player->set_vertical_direction(Player::VerticalDirection::None);
        } else {
            player->set_vertical_direction(Player::VerticalDirection::Up);
        }
    } else {
        if (downPressed) {
            player->set_vertical_direction(Player::VerticalDirection::Down);
        } else {
            player->set_vertical_direction(Player::VerticalDirection::None);
        }
    }

    return false;
}

void Game::update(float time_passed) {
    level->update(time_passed);
}

void Game::draw() {
    level_view.draw();
}
