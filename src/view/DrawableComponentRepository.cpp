#include "DK/view/DrawableComponentRepository.hpp"

void DrawableComponentRepository::draw_all(LayerStack &layer) {
    for (auto it = begin(); it != end(); ++it) {
        it->second->draw(layer);
    }
}

void DrawableComponentRepository::update_all(float dt, Stage &stage) {
    for (auto it = begin(); it != end(); ++it) {
        it->second->update(dt, stage);
    }
}
