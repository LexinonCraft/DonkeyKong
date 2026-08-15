#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "StageTransitionView.hpp"

void StageTransitionView::draw() {
    pre_draw();

    sf::Text title(assets_manager.get_font());
    title.setString("How high can you go?");
    title.setCharacterSize(24);
    sf::FloatRect text_bounds = title.getLocalBounds();
    title.setOrigin({text_bounds.size.x / 2.f, text_bounds.size.y / 2.f});
    title.setPosition({300.f, -300.f});
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(title);

    post_draw();
}
