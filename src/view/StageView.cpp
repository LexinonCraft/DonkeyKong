#include "StageView.hpp"
#include "../model/PlayerData.hpp"

StageView::StageView(sf::RenderWindow &window, Stage &stage, AssetsManager &texture_registry)
    : AbstractSceneView(window, texture_registry),
      drawable_components(stage.get_entities()), stage(stage) {
    // Use the texture_registry as needed
}

void StageView::draw() {
    pre_draw();

    drawable_components.draw_all(layer_stack);

    sf::Text title(assets_manager.get_font());
    title.setString(std::to_string(stage.get_player_data().get_score()));
    title.setCharacterSize(24);
    sf::FloatRect text_bounds = title.getLocalBounds();
    title.setOrigin({text_bounds.size.x / 2.f, text_bounds.size.y / 2.f});
    title.setPosition({300.f, -550.f});
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(title);

    if (stage.get_state() == Stage::StageState::PlayerDied) {
        sf::Text game_over_text(assets_manager.get_font()); // TODO: restart stage if player has enough lifes left, otherwise go to game over screen
        game_over_text.setString("you died!");
        game_over_text.setFillColor(sf::Color::Red);
        game_over_text.setCharacterSize(48);
        sf::FloatRect text_bounds = game_over_text.getLocalBounds();
        game_over_text.setOrigin({text_bounds.size.x / 2.f, text_bounds.size.y / 2.f});
        game_over_text.setPosition({300.f, -300.f});
        layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(game_over_text);
    }

    post_draw();
}
