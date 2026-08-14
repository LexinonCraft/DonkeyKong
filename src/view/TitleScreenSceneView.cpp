#include "TitleScreenSceneView.hpp"
#include <SFML/Graphics/Rect.hpp>

TitleScreenSceneView::TitleScreenSceneView(sf::RenderWindow &window)
    : layer_stack(window),
      window(window) {}

void TitleScreenSceneView::draw() {
    layer_stack.clear_all();

    sf::Font font("assets/fonts/DejaVuSansMono.ttf");

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

    layer_stack.draw_all();
}

void TitleScreenSceneView::set_view(const sf::View &view) {
    layer_stack.get_layer(LayerStack::LayerId::Background).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::Platforms).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::Ladders).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::Objects).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::Player).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::UI).set_view(view);
}
