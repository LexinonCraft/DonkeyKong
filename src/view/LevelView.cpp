#include "LevelView.hpp"
#include <random>

LevelView::LevelView(sf::RenderWindow &window, Level &level)
    : layer_stack(window),
      window(window),
      drawable_components(level.get_entities()) {}

void LevelView::draw() {
    layer_stack.clear_all();

    drawable_components.draw_all(layer_stack);

    layer_stack.draw_all();
}

void LevelView::set_view(const sf::View &view) {
    layer_stack.get_layer(LayerStack::LayerId::Background).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::Platforms).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::Ladders).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::Objects).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::Player).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::UI).set_view(view);
}
