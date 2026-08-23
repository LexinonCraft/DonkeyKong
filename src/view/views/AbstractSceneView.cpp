#include "DK/view/views/AbstractSceneView.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "DK/Constants.hpp"

void AbstractSceneView::adjust_window_view() {
    auto window_size = window.getSize();
    float window_aspect_ratio = static_cast<float>(window_size.x) / static_cast<float>(window_size.y);

    sf::FloatRect viewport({0.f, 0.f}, {1.f, 1.f});
    if (window_aspect_ratio > constants::TARGET_ASPECT_RATIO) {
        float scale = constants::TARGET_ASPECT_RATIO / window_aspect_ratio;
        viewport.position.x = (1.f - scale) / 2.f;
        viewport.size.x = scale;
    } else {
        float scale = window_aspect_ratio / constants::TARGET_ASPECT_RATIO;
        viewport.position.y = (1.f - scale) / 2.f;
        viewport.size.y = scale;
    }

    sf::View view = window.getView();
    view.setViewport(viewport);
    window.setView(view);
}
