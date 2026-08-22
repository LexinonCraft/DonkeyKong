#ifndef LAYER_STACK_HPP
#define LAYER_STACK_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "DK/view/Layer.hpp"

/**
 * @brief Container holding the layered render targets for the game world.
 */
class LayerStack {
public:
    /**
     * @brief Identifies the rendering layer used for a specific object type.
     */
    enum class LayerId {
        Background,
        Ladders,
        Platforms,
        Objects,     // e.g. barrels, ghosts, etc.
        DonkeyKong,
        Player,
        UI,
    };

    /**
     * @brief Creates the stack and initialises all render layers.
     * @param window Window where the layers will be rendered.
     */
    LayerStack(sf::RenderWindow &window);

    /**
     * @brief Returns the render layer for a specific object category.
     * @param id Layer identifier.
     * @return Reference to the corresponding layer.
     */
    Layer &get_layer(LayerId id);

    /**
     * @brief Draws all layers into the window.
     */
    void draw_all();

    /**
     * @brief Clears all internal layer targets and the window.
     */
    void clear_all();

    void set_view(const sf::View &view);

private:
    Layer background_layer;
    Layer platforms_layer;
    Layer ladders_layer;
    Layer donkey_kong_layer;
    Layer objects_layer;
    Layer player_layer;
    Layer ui_layer;

    sf::RenderWindow &window;
};

#endif
