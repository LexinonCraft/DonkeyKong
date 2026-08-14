#ifndef TITLE_SCREEN_VIEW_HPP
#define TITLE_SCREEN_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "LayerStack.hpp"
#include "AssetsManager.hpp"

class TitleScreenView {
public:
    TitleScreenView(sf::RenderWindow &window, AssetsManager &assets_manager);

    void draw();

    /**
     * @brief Applies the active camera view to every render layer.
     * @param view Camera to use for the rendering scene.
     */
    void set_view(const sf::View &view);

private:
    LayerStack layer_stack;
    sf::RenderWindow &window;
    AssetsManager &assets_manager;
};

#endif
