#include "DK/view/views/GameOverView.hpp"

#include <format>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "DK/Constants.hpp"
#include "DK/model/PlayerData.hpp"
#include "DK/util/Positions.hpp"
#include "DK/view/AssetsManager.hpp"

GameOverView::GameOverView(sf::RenderWindow &window, AssetsManager &assets_manager, PlayerData &player_data)
    : AbstractSceneView(window, assets_manager), score(player_data.get_score()) {}

void GameOverView::draw() {
    pre_draw();

    sf::Text title(assets_manager.get_font());
    title.setString("Game over!");
    title.setCharacterSize(constants::GAME_OVER_TITLE_CHARACTER_SIZE);
    set_origin(title, AnchorPosition::Center);
    title.setPosition(get_absolute_position({0.f, constants::GAME_OVER_TITLE_Y}, AnchorPosition::Center));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(title);

    sf::Text score_text(assets_manager.get_font());
    score_text.setString(std::format("Score: {:06d}", score));
    score_text.setCharacterSize(constants::TEXT_CHARACTER_SIZE);
    set_origin(score_text, AnchorPosition::Center);
    score_text.setPosition(get_absolute_position({0.f, constants::GAME_OVER_SCORE_Y}, AnchorPosition::Center));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(score_text);

    post_draw();
}
