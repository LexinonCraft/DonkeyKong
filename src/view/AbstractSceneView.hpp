#ifndef ABSTRACT_SCENE_VIEW_HPP
#define ABSTRACT_SCENE_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "DK/view/LayerStack.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/Constants.hpp"

class AbstractSceneView {
public:
    AbstractSceneView(sf::RenderWindow &window, AssetsManager &assets_manager)
        : layer_stack(window),
          window(window),
          assets_manager(assets_manager) {
        layer_stack.set_view(sf::View(sf::FloatRect(sf::Vector2f({0,-constants::VIEW_HEIGHT}), sf::Vector2f({constants::VIEW_WIDTH,constants::VIEW_HEIGHT}))));
    }

    virtual ~AbstractSceneView() {}

protected:
    LayerStack layer_stack;
    sf::RenderWindow &window;
    AssetsManager &assets_manager;

    void pre_draw() {
        adjust_window_view(window);
        layer_stack.clear_all();
    }

    void post_draw() {
        layer_stack.draw_all();
    }

private:
    static void adjust_window_view(sf::RenderWindow &window);
};

#endif
