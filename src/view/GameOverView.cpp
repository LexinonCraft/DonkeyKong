#include "DK/view/GameOverView.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "DK/util/Positions.hpp"

void GameOverView::draw() {
    pre_draw();

    sf::Text title(assets_manager.get_font());
    title.setString("Game over!");
    title.setCharacterSize(60);
    sf::FloatRect text_bounds = title.getLocalBounds();
    title.setOrigin({text_bounds.size.x / 2.f, text_bounds.size.y / 2.f});
    title.setPosition(get_absolute_position({0.f, 0.f}, AnchorPosition::Center));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(title);

    post_draw();
}
