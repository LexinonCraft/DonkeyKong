#include "LayerStack.hpp"

LayerStack::LayerStack(sf::RenderWindow &window)
    : background_layer(window),
      platforms_layer(window),
      ladders_layer(window),
      donkey_kong_layer(window),
      objects_layer(window),
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
        case LayerId::DonkeyKong:
            return donkey_kong_layer;
        case LayerId::Objects:
            return objects_layer;
        case LayerId::Player:
            return player_layer;
        case LayerId::UI:
            return ui_layer;
    }
    return ui_layer; // Default case, should not happen
}

void LayerStack::draw_all() {
    background_layer.draw();
    ladders_layer.draw();
    platforms_layer.draw();
    objects_layer.draw();
    donkey_kong_layer.draw();
    player_layer.draw();
    ui_layer.draw();

    window.display();
}

void LayerStack::clear_all() {
    window.clear();

    background_layer.clear();
    platforms_layer.clear();
    ladders_layer.clear();
    donkey_kong_layer.clear();
    objects_layer.clear();
    player_layer.clear();
    ui_layer.clear();
}

void LayerStack::set_view(const sf::View &view) {
    background_layer.set_view(view);
    platforms_layer.set_view(view);
    ladders_layer.set_view(view);
    donkey_kong_layer.set_view(view);
    objects_layer.set_view(view);
    player_layer.set_view(view);
    ui_layer.set_view(view);
}
