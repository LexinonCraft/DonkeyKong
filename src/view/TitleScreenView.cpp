#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "TitleScreenView.hpp"
#include "../util/Positions.hpp"

void TitleScreenView::draw() {
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

    sf::Sprite donkey_kong_sprite(assets_manager.get_texture(AssetsManager::TextureId::DonkeyKong));
    donkey_kong_sprite.setPosition(get_absolute_position({0.f, 0.f}, AnchorPosition::Center));
    sf::FloatRect sprite_bounds = donkey_kong_sprite.getLocalBounds();
    donkey_kong_sprite.setOrigin({sprite_bounds.size.x / 2.f, sprite_bounds.size.y / 2.f});
    donkey_kong_sprite.setScale({3.f, 3.f});
    layer_stack.get_layer(LayerStack::LayerId::Background).add_to_layer(donkey_kong_sprite);

    post_draw();
}
