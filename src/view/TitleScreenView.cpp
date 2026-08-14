#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "TitleScreenView.hpp"

TitleScreenView::TitleScreenView(sf::RenderWindow &window, AssetsManager &assets_manager)
    : layer_stack(window),
      window(window),
      assets_manager(assets_manager) {}

void TitleScreenView::draw() {
    layer_stack.clear_all();

    sf::Font font("assets/fonts/PressStart2P.ttf");

    sf::Text title(font);
    title.setString("Donkey Kong");
    title.setCharacterSize(48);
    sf::FloatRect text_bounds = title.getLocalBounds();
    title.setOrigin({text_bounds.size.x / 2.f, text_bounds.size.y / 2.f});
    title.setPosition({300.f, -400.f});
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(title);

    sf::Text subtitle(font);
    subtitle.setString("Press ENTER to Start");
    subtitle.setCharacterSize(24);
    sf::FloatRect subtitle_bounds = subtitle.getLocalBounds();
    subtitle.setOrigin({subtitle_bounds.size.x / 2.f, subtitle_bounds.size.y / 2.f});
    subtitle.setPosition({300.f, -200.f});
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(subtitle);

    sf::Sprite donkey_kong_sprite(assets_manager.get_texture(AssetsManager::TextureId::DonkeyKong));
    donkey_kong_sprite.setPosition({300.f, -300.f});
    sf::FloatRect sprite_bounds = donkey_kong_sprite.getLocalBounds();
    donkey_kong_sprite.setOrigin({sprite_bounds.size.x / 2.f, sprite_bounds.size.y / 2.f});
    donkey_kong_sprite.setScale({3.f, 3.f});
    layer_stack.get_layer(LayerStack::LayerId::Background).add_to_layer(donkey_kong_sprite);

    layer_stack.draw_all();
}

void TitleScreenView::set_view(const sf::View &view) {
    layer_stack.get_layer(LayerStack::LayerId::Background).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::Platforms).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::Ladders).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::Objects).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::Player).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::UI).set_view(view);
}
