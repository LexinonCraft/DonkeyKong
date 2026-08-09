#include "LayerStack.hpp"

LayerStack::LayerStack(sf::RenderWindow &window)
    : background_layer(window),
      platforms_layer(window),
      ladders_layer(window),
      entities_layer(window),
      player_layer(window),
      ui_layer(window),
      window(window) {}

Layer &LayerStack::get_layer(LayerId id) {
    switch (id) {
        case LayerId::Background:
            return background_layer;
        case LayerId::Platforms:
            return platforms_layer;
        case LayerId::Ladders:
            return ladders_layer;
        case LayerId::Entities:
            return entities_layer;
        case LayerId::Player:
            return player_layer;
        case LayerId::UI:
            return ui_layer;
    }
}

void LayerStack::draw_all() {
    background_layer.draw();
    platforms_layer.draw();
    ladders_layer.draw();
    entities_layer.draw();
    player_layer.draw();
    ui_layer.draw();

    window.display();
}

void LayerStack::clear_all() {
    window.clear();

    background_layer.clear();
    platforms_layer.clear();
    ladders_layer.clear();
    entities_layer.clear();
    player_layer.clear();
    ui_layer.clear();
}
