#include "Layer.hpp"

/**
 * @brief Creates an off-screen render layer for one part of the game scene.
 * @param window Window displaying the final scene.
 */
Layer::Layer(sf::RenderWindow &window) :
    window(window),
    target(window.getSize()),
    sprite(target.getTexture()) {
    target.display();
    if (!target.resize(window.getSize()))
        throw std::runtime_error("undefined window size");
}

/**
 * @brief Adds a drawable object to the layered render target.
 * @param drawable SFML drawable to include in the layer.
 */
void Layer::add_to_layer(const sf::Drawable &drawable) {
    target.draw(drawable);
}

/**
 * @brief Presents the layer texture in the main render window.
 */
void Layer::draw() {
    // update the render target and draw it inside the window
    target.display();
    window.draw(sprite);
}

/**
 * @brief Clears all objects currently added to the layer.
 */
void Layer::clear() {
    target.clear({0,0,0,0});
}

/**
 * @brief Applies the active camera view to the layer.
 * @param view Camera state used for rendering.
 */
void Layer::set_view(const sf::View &view) {
    target.setView(view);
}
