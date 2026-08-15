#include "StageView.hpp"
#include "../model/PlayerData.hpp"

StageView::StageView(sf::RenderWindow &window, Stage &stage, AssetsManager &texture_registry)
    : AbstractSceneView(window, texture_registry),
      drawable_components(stage.get_entities(), assets_manager), stage(stage) {
    // Use the texture_registry as needed
}

void StageView::draw() {
    pre_draw();

    drawable_components.draw_all(layer_stack);

    sf::Text score(assets_manager.get_font());
    score.setString(std::to_string(stage.get_player_data().get_score()));
    score.setCharacterSize(24);
    sf::FloatRect score_bounds = score.getLocalBounds();
    score.setOrigin({score_bounds.size.x / 2.f, score_bounds.size.y / 2.f});
    score.setPosition({300.f, -550.f});
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(score);

    int lives_count = stage.get_player_data().get_lives();
    for (int i = 0; i < lives_count; ++i) {
        sf::Sprite life_sprite(assets_manager.get_texture(AssetsManager::TextureId::Jumpman));
        life_sprite.setPosition({50.f + (i * 20.f), -520.f});
        sf::FloatRect sprite_bounds = life_sprite.getLocalBounds();
        life_sprite.setOrigin({sprite_bounds.size.x / 2.f, sprite_bounds.size.y / 2.f});
        // life_sprite.setScale({0.5f, 0.5f});
        layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(life_sprite);
    }

    if (stage.get_state() == Stage::StageState::PlayerDying) {
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
