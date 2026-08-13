#ifndef ABSTRACT_SCENE_CONTROL_HPP
#define ABSTRACT_SCENE_CONTROL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../model/Constants.hpp"

class AbstractSceneControl {
public:
    AbstractSceneControl(sf::RenderWindow &window) : view(sf::FloatRect(sf::Vector2f({0,-constants::VIEW_HEIGHT}), sf::Vector2f({constants::VIEW_WIDTH,constants::VIEW_HEIGHT}))), window(window) {}

    virtual ~AbstractSceneControl() {}

    virtual bool handle_input() = 0;

    virtual void update(float dt) = 0;

    virtual void draw() = 0;

protected:
    sf::View view;
    sf::RenderWindow &window;
};

#endif
