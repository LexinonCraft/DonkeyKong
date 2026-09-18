#include "DK/view/views/TitleScreenView.hpp"

#include <format>
#include <stdexcept>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "DK/Constants.hpp"
#include "DK/model/PlayerData.hpp"
#include "DK/util/Math.hpp"
#include "DK/util/Positions.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/LayerStack.hpp"

void TitleScreenView::draw() {
    pre_draw();

    // Game title
    sf::Text title(assets_manager.get_font());
    title.setString("Donkey Kong");
    title.setCharacterSize(constants::TITLE_SCREEN_TITLE_CHARACTER_SIZE);
    set_origin(title, AnchorPosition::Center);
    title.setPosition(get_absolute_position({0.f, constants::TITLE_SCREEN_TITLE_Y}, AnchorPosition::Center));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(title);

    // "Press ENTER to start" text
    sf::Text start_text(assets_manager.get_font());
    start_text.setString("Press ENTER to start");
    start_text.setCharacterSize(constants::TEXT_CHARACTER_SIZE);
    set_origin(start_text, AnchorPosition::Center);
    start_text.setPosition(get_absolute_position({0.f, constants::TITLE_SCREEN_START_TEXT_Y}, AnchorPosition::Center));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(start_text);

    // Animated Donkey Kong
    AssetsManager::TextureId donkey_kong_texture_id;
    bool flip;
    if (animation_timer < constants::TITLE_SCREEN_ANGRY_FRAME_COUNT * constants::DONKEY_KONG_ANGRY_ANIMATION_INTERVAL) {
        switch (mod(floor_to_int(animation_timer / constants::DONKEY_KONG_ANGRY_ANIMATION_INTERVAL),
                    constants::TITLE_SCREEN_ANGRY_FRAME_COUNT)) {
            case 0:
                donkey_kong_texture_id = AssetsManager::TextureId::DonkeyKongAngry1;
                flip = false;
                break;
            case 1:
                donkey_kong_texture_id = AssetsManager::TextureId::DonkeyKongAngry1;
                flip = true;
                break;
            case 2:
                donkey_kong_texture_id = AssetsManager::TextureId::DonkeyKongAngry1;
                flip = false;
                break;
            default:
                throw std::logic_error("Unexpected case in donkey kong animation switch statement");
        }
    } else {
        donkey_kong_texture_id = AssetsManager::TextureId::DonkeyKongStill;
        flip = false;
    }
    sf::Sprite donkey_kong_sprite(assets_manager.get_texture(donkey_kong_texture_id));
    donkey_kong_sprite.setPosition(get_absolute_position({0.f, 0.f}, AnchorPosition::Center));
    set_origin(donkey_kong_sprite, AnchorPosition::Center);
    scale(donkey_kong_sprite, constants::TITLE_SCREEN_DONKEY_KONG_SCALE);
    flip_horizontally(donkey_kong_sprite, flip);
    layer_stack.get_layer(LayerStack::LayerId::Background).add_to_layer(donkey_kong_sprite);

    // Contributors text
    sf::Text contributors(assets_manager.get_font());
    contributors.setString(assets_manager.get_contributors());
    contributors.setCharacterSize(constants::TITLE_SCREEN_CONTRIBUTORS_CHARACTER_SIZE);
    set_origin(contributors, AnchorPosition::Center);
    contributors.setPosition(get_absolute_position({0.f, constants::TITLE_SCREEN_CONTRIBUTORS_Y}, AnchorPosition::BottomCenter));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(contributors);

    // Highscore label
    sf::Text highscore_label(assets_manager.get_font());
    highscore_label.setString("HIGH SCORE");
    highscore_label.setFillColor(sf::Color::Red);
    highscore_label.setCharacterSize(constants::TEXT_CHARACTER_SIZE);
    set_origin(highscore_label, AnchorPosition::TopCenter);
    highscore_label.setPosition(get_absolute_position({0.f, constants::TITLE_SCREEN_HIGHSCORE_LABEL_Y}, AnchorPosition::TopCenter));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(highscore_label);

    // Highscore
    sf::Text highscore(assets_manager.get_font());
    highscore.setString(std::format("{:06d}", player_data.get_highscore()));
    highscore.setCharacterSize(constants::TEXT_CHARACTER_SIZE);
    set_origin(highscore, AnchorPosition::TopCenter);
    highscore.setPosition(get_absolute_position({0.f, constants::TITLE_SCREEN_HIGHSCORE_Y}, AnchorPosition::TopCenter));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(highscore);

    post_draw();
}

void TitleScreenView::update(float dt) {
    animation_timer += dt;
    if (animation_timer >= constants::TITLE_SCREEN_ANIMATION_LENGTH) {
        animation_timer -= constants::TITLE_SCREEN_ANIMATION_LENGTH;
    }
}
