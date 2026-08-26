#include "DK/view/ScoreEffect.hpp"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>

#include "DK/Constants.hpp"
#include "DK/view/AssetsManager.hpp"
#include "DK/view/LayerStack.hpp"

void ScoreEffect::draw(LayerStack &layer_stack, AssetsManager &assets_manager) {
    float rise_distance = constants::SCORE_EFFECT_RISE_SPEED * time_elapsed;
    sf::Vector2f position = origin - sf::Vector2f(0.f, rise_distance);

    sf::Text text(assets_manager.get_font());
    text.setString(std::to_string(added_score));
    text.setCharacterSize(constants::SCORE_EFFECT_CHARACTER_SIZE);
    sf::FloatRect text_bounds = text.getLocalBounds();
    text.setOrigin({text_bounds.size.x / 2.f, text_bounds.size.y / 2.f});
    text.setPosition(position);
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(text);
}
