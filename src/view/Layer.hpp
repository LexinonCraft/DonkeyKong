#ifndef LAYER_HPP
#define LAYER_HPP

#include <SFML/Graphics.hpp>

/**
 * @brief Offscreen render layer that collects drawables before transferring them to the window.
 */
class Layer {
public:
    /**
     * @brief Creates a layer bound to a given render window.
     * @param window Window that will display the final layer content.
     */
    Layer(sf::RenderWindow &window);

    /**
     * @brief Adds an SFML drawable object to this layer.
     * @param drawable Drawable object to render into the layer.
     */
    void add_to_layer(const sf::Drawable &drawable);

    /**
     * @brief Uploads the layer texture to the window and presents it.
     */
    void draw();

    /**
     * @brief Clears the layer contents while preserving the underlying window.
     */
    void clear();

    /**
     * @brief Sets the view used when rendering this layer.
     * @param view Camera/view state to apply.
     */
    void set_view(const sf::View &view);

private:
    sf::RenderWindow &window;
    sf::RenderTexture target;
    sf::Sprite sprite;
};

#endif