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
    if (animation_timer < 3 * 0.5f) { // TODO: use constant for frame length once available
        switch (mod(floor_to_int(animation_timer / 0.5f), 3)) { // TODO: see above
            case 0:
                donkey_kong_texture_id = AssetsManager::TextureId::DonkeyKong; // TODO: switch to specific texture once available
                break;
            case 1:
                donkey_kong_texture_id = AssetsManager::TextureId::DonkeyKong; // TODO: see above
                break;
            case 2:
                donkey_kong_texture_id = AssetsManager::TextureId::DonkeyKong; // TODO: see above
                break;
            default:
                throw std::logic_error("Unexpected case in donkey kong animation switch statement");
        }
        donkey_kong_texture_id = AssetsManager::TextureId::DonkeyKong; // TODO: see above
    } else {
        donkey_kong_texture_id = AssetsManager::TextureId::DonkeyKong; // TODO: see above
    }
    sf::Sprite donkey_kong_sprite(assets_manager.get_texture(donkey_kong_texture_id));
    donkey_kong_sprite.setPosition(get_absolute_position({0.f, 0.f}, AnchorPosition::Center));
    sf::FloatRect sprite_bounds = donkey_kong_sprite.getLocalBounds();
    donkey_kong_sprite.setOrigin({sprite_bounds.size.x / 2.f, sprite_bounds.size.y / 2.f});
    donkey_kong_sprite.setScale({3.f, 3.f});
    layer_stack.get_layer(LayerStack::LayerId::Background).add_to_layer(donkey_kong_sprite);

    post_draw();
}
