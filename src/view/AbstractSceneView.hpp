#ifndef ABSTRACT_SCENE_VIEW_HPP
#define ABSTRACT_SCENE_VIEW_HPP

#include <SFML/Graphics.hpp>

class AbstractSceneView {
public:
    virtual ~AbstractSceneView() {}

    virtual void draw() = 0;

    virtual void set_view(const sf::View &view) = 0;
};

#endif
