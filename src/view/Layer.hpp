#ifndef LAYER_HPP
#define LAYER_HPP

#include <SFML/Graphics.hpp>

#include "DK/Constants.hpp"

/**
 * @brief Offscreen render layer that collects drawables before transferring them to the window.
 */
class Layer {
public:
    /**
     * @brief Creates a layer bound to a given render window.
     * @param window Window that will display the final layer content.
     */
    Layer(sf::RenderWindow &window) : window(window), target({constants::VIEW_WIDTH, constants::VIEW_HEIGHT}), sprite(target.getTexture()) {
        target.display();
    }

    /**
     * @brief Adds an SFML drawable object to this layer.
     * @param drawable Drawable object to render into the layer.
     */
    void add_to_layer(const sf::Drawable &drawable) { target.draw(drawable); }

    /**
     * @brief Uploads the layer texture to the window and presents it.
     */
    void draw() {
        target.display();
        window.draw(sprite);
    }

    /**
     * @brief Clears the layer contents while preserving the underlying window.
     */
    void clear() {
        resize_to_viewport();
        target.clear({0, 0, 0, 0});
    }

    /**
     * @brief Sets the view used when rendering this layer.
     * @param view Camera/view state to apply.
     */
    void set_view(const sf::View &view) { target.setView(view); }

private:
    sf::RenderWindow &window;
    sf::RenderTexture target;
    sf::Sprite sprite;

    /**
     * @brief When the window is resized, this method resizes the render target to match the new viewport size.
     */
    void resize_to_viewport();
};

#endif
