#include "DK/view/views/StageView.hpp"

#include <format>

#include <SFML/Graphics/Color.hpp>

#include "DK/model/PlayerData.hpp"
#include "DK/util/Positions.hpp"

StageView::StageView(sf::RenderWindow &window, Stage &stage, AssetsManager &texture_registry)
    : AbstractSceneView(window, texture_registry), drawable_components(stage.get_entities(), assets_manager), stage(stage) {
    stage_observer_id = stage.get_observer_registry().register_observer(*this);
}

StageView::~StageView() { stage.get_observer_registry().unregister_observer(stage_observer_id); }

void StageView::draw() {
    pre_draw();

    // Drawable entities
    drawable_components.draw_all(layer_stack);

    // Label for score
    sf::Text score_label(assets_manager.get_font());
    score_label.setString("1 UP");
    score_label.setFillColor(sf::Color::Red);
    score_label.setCharacterSize(24);
    set_origin(score_label, AnchorPosition::TopCenter);
    score_label.setPosition(get_absolute_position({70.f, 0.f}, AnchorPosition::TopLeft));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(score_label);

    // Score
    sf::Text score(assets_manager.get_font());
    score.setString(std::format("{:06d}", stage.get_player_data().get_score()));
    score.setCharacterSize(24);
    set_origin(score, AnchorPosition::TopCenter);
    score.setPosition(get_absolute_position({70.f, 24.f}, AnchorPosition::TopLeft));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(score);

    // Label for highscore
    sf::Text highscore_label(assets_manager.get_font());
    highscore_label.setString("HIGH SCORE");
    highscore_label.setFillColor(sf::Color::Red);
    highscore_label.setCharacterSize(24);
    set_origin(highscore_label, AnchorPosition::TopCenter);
    highscore_label.setPosition(get_absolute_position({0.f, 0.f}, AnchorPosition::TopCenter));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(highscore_label);

    // Highscore
    sf::Text highscore(assets_manager.get_font());
    highscore.setString(std::format("{:06d}", stage.get_player_data().get_highscore()));
    highscore.setCharacterSize(24);
    set_origin(highscore, AnchorPosition::TopCenter);
    highscore.setPosition(get_absolute_position({0.f, 24.f}, AnchorPosition::TopCenter));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(highscore);

    // Symbol for hammer count
    sf::Sprite hammer_sprite(assets_manager.get_texture(AssetsManager::TextureId::Hammer));
    set_origin(hammer_sprite, AnchorPosition::Center);
    hammer_sprite.setPosition(get_absolute_position({30.f, 104.f}, AnchorPosition::TopLeft));
    scale(hammer_sprite, 2.f);
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(hammer_sprite);

    // Hammer count
    sf::Text hammer_count(assets_manager.get_font());
    hammer_count.setString(std::format("{:d}", stage.get_player_data().get_hammer_use_count()));
    hammer_count.setCharacterSize(24);
    sf::FloatRect hammer_count_bounds = hammer_count.getLocalBounds();
    hammer_count.setOrigin({0.f, hammer_count_bounds.size.y / 2.f});
    hammer_count.setPosition(get_absolute_position({50.f, 110.f}, AnchorPosition::TopLeft));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(hammer_count);

    // Symbol for barrel count
    sf::Sprite barrel_sprite(assets_manager.get_texture(AssetsManager::TextureId::BarrelFront1));
    set_origin(barrel_sprite, AnchorPosition::Center);
    barrel_sprite.setPosition(get_absolute_position({30.f, 140.f}, AnchorPosition::TopLeft));
    scale(barrel_sprite, 2.f);
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(barrel_sprite);

    // Barrel count
    sf::Text barrel_count(assets_manager.get_font());
    barrel_count.setString(std::format("{:d}", stage.get_player_data().get_jumped_over_barrels_count()));
    barrel_count.setCharacterSize(24);
    sf::FloatRect barrel_count_bounds = barrel_count.getLocalBounds();
    barrel_count.setOrigin({0.f, barrel_count_bounds.size.y / 2.f});
    barrel_count.setPosition(get_absolute_position({50.f, 140.f}, AnchorPosition::TopLeft));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(barrel_count);

    // Lives
    int lives_count = stage.get_player_data().get_lives();
    for (int i = 0; i < lives_count; ++i) {
        sf::Sprite life_sprite(assets_manager.get_texture(AssetsManager::TextureId::JumpmanStill));
        life_sprite.setPosition(get_absolute_position({30.f + (i * 30.f), 80.f}, AnchorPosition::TopLeft));
        set_origin(life_sprite, AnchorPosition::Center);
        scale(life_sprite, 2.f);
        layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(life_sprite);
    }

    // Level
    sf::Text level_text(assets_manager.get_font());
    level_text.setString(std::format("L={:02d}", stage.get_player_data().get_level() + 1));
    level_text.setCharacterSize(24);
    set_origin(level_text, AnchorPosition::Center);
    level_text.setPosition(get_absolute_position({-100.f, 100.f}, AnchorPosition::TopRight));
    level_text.setFillColor(sf::Color::Blue);
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(level_text);

    // Score effects
    for (auto it = current_score_effects.begin(); it != current_score_effects.end(); ++it) {
        it->draw(layer_stack, assets_manager);
    }

    post_draw();
}

void StageView::update(float dt) {
    for (auto it = current_score_effects.begin(); it != current_score_effects.end();) {
        if (!it->update(dt)) {
            it = current_score_effects.erase(it);
        } else {
            ++it;
        }
    }

    drawable_components.update_all(dt, stage);
}
