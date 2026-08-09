#ifndef LAYER_STACK_H
#define LAYER_STACK_H

#include "Layer.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class LayerStack {
public:
    enum class LayerId {
        Background,
        Platforms,
        Ladders,
        Objects,
        Player,
        UI,
    };

    LayerStack(sf::RenderWindow &window);

    Layer &get_layer(LayerId id);

    void draw_all();

    void clear_all();

private:
    Layer background_layer;
    Layer platforms_layer;
    Layer ladders_layer;
    Layer objects_layer;
    Layer player_layer;
    Layer ui_layer;

    sf::RenderWindow &window;
};

#endif
