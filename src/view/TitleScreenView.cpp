#include <stdexcept>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "TitleScreenView.hpp"
#include "../util/Positions.hpp"
#include "../util/Math.hpp"

void TitleScreenView::draw(float animation_timer) {
    pre_draw();

    sf::Text title(assets_manager.get_font());
    title.setString("Donkey Kong");
    title.setCharacterSize(48);
    sf::FloatRect text_bounds = title.getLocalBounds();
    title.setOrigin({text_bounds.size.x / 2.f, text_bounds.size.y / 2.f});
    title.setPosition(get_absolute_position({0.f, -100.f}, AnchorPosition::Center));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(title);

    sf::Text subtitle(assets_manager.get_font());
    subtitle.setString("Press ENTER to Start");
    subtitle.setCharacterSize(24);
    sf::FloatRect subtitle_bounds = subtitle.getLocalBounds();
    subtitle.setOrigin({subtitle_bounds.size.x / 2.f, subtitle_bounds.size.y / 2.f});
    subtitle.setPosition(get_absolute_position({0.f, 100.f}, AnchorPosition::Center));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(subtitle);

    AssetsManager::TextureId donkey_kong_texture_id;
    bool flip;
    if (animation_timer < 3 * constants::DONKEY_KONG_ANGRY_ANIMATION_INTERVAL) {
        switch (mod(floor_to_int(animation_timer / constants::DONKEY_KONG_ANGRY_ANIMATION_INTERVAL), 3)) {
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
    sf::FloatRect sprite_bounds = donkey_kong_sprite.getLocalBounds();
    donkey_kong_sprite.setOrigin({sprite_bounds.size.x / 2.f, sprite_bounds.size.y / 2.f});
    donkey_kong_sprite.setScale({flip ? -3.f : 3.f, 3.f});
    layer_stack.get_layer(LayerStack::LayerId::Background).add_to_layer(donkey_kong_sprite);

    sf::Text contributors(assets_manager.get_font());
    contributors.setString(assets_manager.get_contributors());
    contributors.setCharacterSize(6);
    sf::FloatRect contributors_bounds = contributors.getLocalBounds();
    contributors.setOrigin({contributors_bounds.size.x / 2.f, contributors_bounds.size.y / 2.f});
    contributors.setPosition(get_absolute_position({0.f, -50.f}, AnchorPosition::BottomCenter));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(contributors);

    post_draw();
}
