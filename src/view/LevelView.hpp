#ifndef LEVEL_VIEW_HPP
#define LEVEL_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "LayerStack.hpp"
#include "../model/Level.hpp"
#include "DrawableComponentRepository.hpp"

/**
 * @brief View component that renders a whole level using layered SFML textures.
 */
class LevelView {
public:
    /**
     * @brief Creates the level view and binds it to a specific level.
     * @param window Window used for rendering.
     * @param level Level whose entities are rendered.
     */
    LevelView(sf::RenderWindow &window, Level &level);

    /**
     * @brief Renders the current state of the level.
     */
    void draw();

    /**
     * @brief Applies the active camera view to every render layer.
     * @param view Camera to use for the rendering scene.
     */
    void set_view(const sf::View &view);

private:
    LayerStack layer_stack;
    sf::RenderWindow &window;
    DrawableComponentRepository drawable_components;
};

#endif
