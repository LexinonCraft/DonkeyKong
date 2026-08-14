#ifndef TITLE_SCREEN_SCENE_VIEW_HPP
#define TITLE_SCREEN_SCENE_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "AbstractSceneView.hpp"
#include "LayerStack.hpp"

class TitleScreenSceneView : public AbstractSceneView {
public:
    TitleScreenSceneView(sf::RenderWindow &window);

    void draw() override;

    /**
     * @brief Applies the active camera view to every render layer.
     * @param view Camera to use for the rendering scene.
     */
    void set_view(const sf::View &view) override;

private:
    LayerStack layer_stack;
    sf::RenderWindow &window;
};

#endif
