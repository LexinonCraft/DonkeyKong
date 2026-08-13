#include "StageControl.hpp"

bool StageControl::handle_input() {
    std::shared_ptr<Player> player = stage->get_player();

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

void StageControl::update(float dt) {
    stage->update(dt);
}

void StageControl::draw() {
    stage_view.draw();
}
