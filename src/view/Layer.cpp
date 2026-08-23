#include "DK/view/Layer.hpp"

#include <stdexcept>

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
