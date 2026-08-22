#ifndef ABSTRACT_SCENE_VIEW_HPP
#define ABSTRACT_SCENE_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "DK/Constants.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/LayerStack.hpp"

/**
 * @brief Basic funtionality for a scene view. It handles the window view and the layer stack.
 */
class AbstractSceneView {
public:
    /**
     * @brief Stores the window and the assets manager, and sets the view of the layer stack to the default view.
     *
     * @param window The window to draw to
     * @param assets_manager The assets manager to retrieve assets from
     */
    AbstractSceneView(sf::RenderWindow &window, AssetsManager &assets_manager)
        : layer_stack(window), window(window), assets_manager(assets_manager) {
        layer_stack.set_view(sf::View(
            sf::FloatRect(sf::Vector2f({0, -constants::VIEW_HEIGHT}), sf::Vector2f({constants::VIEW_WIDTH, constants::VIEW_HEIGHT}))));
    }

    virtual ~AbstractSceneView() = default;

protected:
    LayerStack layer_stack;
    sf::RenderWindow &window;
    AssetsManager &assets_manager;

    /**
     * @brief Prepares the scene for drawing by adjusting the window view and clearing all layers.
     */
    void pre_draw() {
        adjust_window_view();
        layer_stack.clear_all();
    }

    /**
     * @brief Finalizes the drawing of the scene by drawing all layers to the window.
     */
    void post_draw() { layer_stack.draw_all(); }

private:
    /**
    * @brief Adjust the view of the window to maintain the target aspect ratio.
    * 
    * @param window 
    */
    void adjust_window_view();
};

#endif
