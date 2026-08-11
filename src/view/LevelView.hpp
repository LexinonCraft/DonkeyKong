#ifndef LEVEL_VIEW_HPP
#define LEVEL_VIEW_HPP

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
