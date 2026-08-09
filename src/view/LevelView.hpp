#ifndef LEVEL_VIEW_H
#define LEVEL_VIEW_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "LayerStack.hpp"
#include "../model/Level.hpp"
#include "DrawableComponentRepository.hpp"

class LevelView {
public:
    LevelView(sf::RenderWindow &window, Level &level);

    void draw();

    void set_view(const sf::View &view);

private:
    LayerStack layer_stack;
    sf::RenderWindow &window;
    DrawableComponentRepository drawable_components;
};

#endif
