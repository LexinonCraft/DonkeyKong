#include "DrawableComponentRepository.hpp"

void DrawableComponentRepository::draw_all(LayerStack &layer) {
    for (auto it = begin(); it != end(); ++it) {
        it->second->draw(layer);
    }
}
