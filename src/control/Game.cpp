#include "Game.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <memory>

#include "../model/Constants.hpp"
#include "../model/DemoLevel.hpp"
#include "../model/Entity.hpp"
#include "PlatformPainter.hpp"
#include "EntityPainter.hpp"
#include "../model/Player.hpp"

Game::Game() :
    window(sf::VideoMode({constants::VIEW_WIDTH, constants::VIEW_HEIGHT}), "Donkey Kong"),
    view(sf::FloatRect(sf::Vector2f({0,-constants::VIEW_HEIGHT}), sf::Vector2f({constants::VIEW_WIDTH,constants::VIEW_HEIGHT}))),
    game_layer(window),
    level(new DemoLevel(std::rand)) {
        // limit frame rate
        window.setFramerateLimit(constants::FRAME_RATE);

        // set the view (visible area) for our game
        game_layer.set_view(view);

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
    std::shared_ptr<Player> player = level->get_player();

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
    //player_control.update(*level, time_passed);
}

void Game::draw() {
    window.clear();

    game_layer.clear();
    // TODO: move this to view classes
    PlatformPainter platform_painter(game_layer);
    for (auto it = level->get_platforms().begin(); it != level->get_platforms().end(); ++it) {
        it->second->accept(platform_painter);
    }
    for (auto it = level->get_ladders().begin(); it != level->get_ladders().end(); ++it) {
        game_layer.add_to_layer(it->second->get_shape());
    }
    EntityPainter entity_painter(game_layer);
    for (auto it = level->get_entities().begin(); it != level->get_entities().end(); ++it) {
        it->second->accept(entity_painter);
    }
    game_layer.draw();

    window.display();
}
