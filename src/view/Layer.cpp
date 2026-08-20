#include "Layer.hpp"
#include "../Constants.hpp"

#include <stdexcept>

/**
 * @brief Creates an off-screen render layer for one part of the game scene.
 * @param window Window displaying the final scene.
 */
Layer::Layer(sf::RenderWindow &window) :
    window(window),
    target({constants::VIEW_WIDTH, constants::VIEW_HEIGHT}),
    sprite(target.getTexture()) {
    target.display();
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
    resize_to_viewport();
    target.clear({0,0,0,0});
}

/**
 * @brief Applies the active camera view to the layer.
 * @param view Camera state used for rendering.
 */
void Layer::set_view(const sf::View &view) {
    target.setView(view);
}

void Layer::resize_to_viewport() {
    const sf::Vector2i viewport_size = window.getViewport(window.getView()).size;
    if (viewport_size.x <= 0 || viewport_size.y <= 0) {
        return;
    }

    const sf::Vector2u target_size{static_cast<unsigned int>(viewport_size.x), static_cast<unsigned int>(viewport_size.y)};
    if (target.getSize() == target_size) {
        return;
    }

    const sf::View view = target.getView();
    if (!target.resize(target_size)) {
        throw std::runtime_error("Failed to resize render layer");
    }

    target.setView(view);
    sprite.setTexture(target.getTexture(), true);
    sprite.setScale({static_cast<float>(constants::VIEW_WIDTH) / static_cast<float>(target_size.x),
                     static_cast<float>(constants::VIEW_HEIGHT) / static_cast<float>(target_size.y)});
}
