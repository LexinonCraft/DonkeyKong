#include "StageView.hpp"

StageView::StageView(sf::RenderWindow &window, Stage &level, AssetsManager &texture_registry)
    : AbstractSceneView(window, texture_registry),
      drawable_components(level.get_entities()) {
    // Use the texture_registry as needed
}

void StageView::draw() {
    pre_draw();
    drawable_components.draw_all(layer_stack);
    post_draw();
}
