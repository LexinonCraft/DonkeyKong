#include "DK/view/views/GameOverView.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "DK/util/Positions.hpp"
#include "DK/view/AssetsManager.hpp"

void GameOverView::draw() {
    pre_draw();

    sf::Text title(assets_manager.get_font());
    title.setString("Game over!");
    title.setCharacterSize(60);
    set_origin(title, AnchorPosition::Center);
    title.setPosition(get_absolute_position({0.f, 0.f}, AnchorPosition::Center));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(title);

    post_draw();
}
