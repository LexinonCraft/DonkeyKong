#include "StageControl.hpp"

void StageControl::handle_event(sf::Event *event) {
    if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Space) {
            stage->get_player()->jump();
            stage->get_player_data().add_to_score(10);  // add points for jumping (only for demonstration purposes)
        }
    }
}

void StageControl::handle_input() {
    auto player = stage->get_player();

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
}

void StageControl::update(float dt) {
    stage->update(dt);
}

void StageControl::draw() {
    stage_view.draw();
}

AbstractSceneControl::NextScene StageControl::get_next_scene() const {
    if (!stage->is_over()) {
        return AbstractSceneControl::NextScene::Stay;
    }

    return stage->on_exit() ? AbstractSceneControl::NextScene::StageTransition : AbstractSceneControl::NextScene::GameOver;
}
