#include "DrawableComponentRepository.hpp"

/**
 * @brief Draws every registered drawable component into the provided layer stack.
 * @param layer Layer stack receiving the scene draw calls.
 */
void DrawableComponentRepository::draw_all(LayerStack &layer) {
    for (auto it = begin(); it != end(); ++it) {
        it->second->draw(layer);
    }
}

void DrawableComponentRepository::update_all(float dt) {
    for (auto it = begin(); it != end(); ++it) {
        it->second->update(dt);
    }
}
