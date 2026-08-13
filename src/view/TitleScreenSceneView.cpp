#include "TitleScreenSceneView.hpp"

TitleScreenSceneView::TitleScreenSceneView(sf::RenderWindow &window, TitleScreenScene &scene)
    : layer_stack(window),
      window(window) {}

void TitleScreenSceneView::draw() {
    layer_stack.clear_all();

    sf::Font font("assets/fonts/DejaVuSansMono.ttf");
    sf::Text title(font);
    title.setString("Donkey Kong");
    title.setCharacterSize(48);
    title.setPosition({0.f, -200.f});
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(title);

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
