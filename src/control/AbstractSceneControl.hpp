#ifndef ABSTRACT_SCENE_CONTROL_HPP
#define ABSTRACT_SCENE_CONTROL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class AbstractSceneControl {
public:
    enum class NextScene {
        Stay,
        MainMenu,
        StageTransition,
        Stage,
        GameOver,
    };

    AbstractSceneControl(sf::RenderWindow &window) : window(window) {}

    virtual ~AbstractSceneControl() {}

    virtual void handle_event(sf::Event *event) = 0;

    virtual void handle_input() = 0;

    virtual void update(float dt) = 0;

    virtual void draw() = 0;

    virtual NextScene get_next_scene() const = 0;

protected:
    sf::RenderWindow &window;
};

#endif
