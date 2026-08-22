#include "DK/control/StageControl.hpp"

#include <SFML/Window/Keyboard.hpp>

void StageControl::handle_event(sf::Event *event) {
    if (const auto *key_pressed = event->getIf<sf::Event::KeyPressed>()) {
        switch (key_pressed->code) {
            case sf::Keyboard::Key::Space:
                stage->get_player()->jump();
                break;
            case sf::Keyboard::Key::Left:
                left_pressed = true;
                break;
            case sf::Keyboard::Key::Right:
                right_pressed = true;
                break;
            case sf::Keyboard::Key::Up:
                up_pressed = true;
                break;
            case sf::Keyboard::Key::Down:
                down_pressed = true;
                break;
            default:
                break;
        }
    }

    if (const auto *key_released = event->getIf<sf::Event::KeyReleased>()) {
        switch (key_released->code) {
            case sf::Keyboard::Key::Left:
                left_pressed = false;
                break;
            case sf::Keyboard::Key::Right:
                right_pressed = false;
                break;
            case sf::Keyboard::Key::Up:
                up_pressed = false;
                break;
            case sf::Keyboard::Key::Down:
                down_pressed = false;
                break;
            default:
                break;
        }
    }

    if (event->is<sf::Event::FocusLost>()) {
        left_pressed = false;
        right_pressed = false;
        up_pressed = false;
        down_pressed = false;
    }
}

void StageControl::handle_input() {
    auto player = stage->get_player();

    if (left_pressed) {
        if (right_pressed) {
            player->set_horizontal_direction(Player::HorizontalDirection::None);
        } else {
            player->set_horizontal_direction(Player::HorizontalDirection::Left);
        }
    } else {
        if (right_pressed) {
            player->set_horizontal_direction(Player::HorizontalDirection::Right);
        } else {
            player->set_horizontal_direction(Player::HorizontalDirection::None);
        }
    }

    if (up_pressed) {
        if (down_pressed) {
            player->set_vertical_direction(Player::VerticalDirection::None);
        } else {
            player->set_vertical_direction(Player::VerticalDirection::Up);
        }
    } else {
        if (down_pressed) {
            player->set_vertical_direction(Player::VerticalDirection::Down);
        } else {
            player->set_vertical_direction(Player::VerticalDirection::None);
        }
    }
}

void StageControl::update(float dt) {
    stage->update(dt);
    stage_view.update(dt, *stage);
}

void StageControl::draw() { stage_view.draw(); }

AbstractSceneControl::NextScene StageControl::get_next_scene() const {
    if (!stage->is_over()) {
        return AbstractSceneControl::NextScene::Stay;
    }

    return stage->get_player_data().get_lives() > 0 ? AbstractSceneControl::NextScene::StageTransition
                                                    : AbstractSceneControl::NextScene::GameOver;
}
