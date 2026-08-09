#include "LevelView.hpp"
#include "PlatformPainter.hpp"
#include "EntityPainter.hpp"

LevelView::LevelView(sf::RenderWindow &window, Level &level)
    : layer_stack(window),
      window(window),
      level(level) {}

void LevelView::draw() {
    layer_stack.clear_all();

    PlatformPainter platform_painter(layer_stack.get_layer(LayerStack::LayerId::Platforms));
    for (auto it = level.get_platforms().begin(); it != level.get_platforms().end(); ++it) {
        it->second->accept(platform_painter);
    }
    for (auto it = level.get_ladders().begin(); it != level.get_ladders().end(); ++it) {
        layer_stack.get_layer(LayerStack::LayerId::Ladders).add_to_layer(it->second->get_shape());
    }
    EntityPainter entity_painter(layer_stack.get_layer(LayerStack::LayerId::Entities));
    for (auto it = level.get_entities().begin(); it != level.get_entities().end(); ++it) {
        it->second->accept(entity_painter);
    }

    layer_stack.draw_all();
}

void LevelView::set_view(const sf::View &view) {
    layer_stack.get_layer(LayerStack::LayerId::Background).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::Platforms).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::Ladders).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::Entities).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::Player).set_view(view);
    layer_stack.get_layer(LayerStack::LayerId::UI).set_view(view);
}
