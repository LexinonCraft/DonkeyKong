#include "DK/view/StageView.hpp"

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

    drawable_components.draw_all(layer_stack);

    sf::Text score_label(assets_manager.get_font());
    score_label.setString("1 UP");
    score_label.setFillColor(sf::Color::Red);
    score_label.setCharacterSize(24);
    sf::FloatRect score_label_bounds = score_label.getLocalBounds();
    score_label.setOrigin({score_label_bounds.size.x / 2.f, 0.f});
    score_label.setPosition(get_absolute_position({70.f, 0.f}, AnchorPosition::TopLeft));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(score_label);

    sf::Text score(assets_manager.get_font());
    score.setString(std::format("{:06d}", stage.get_player_data().get_score()));
    score.setCharacterSize(24);
    sf::FloatRect score_bounds = score.getLocalBounds();
    score.setOrigin({score_bounds.size.x / 2.f, 0.f});
    score.setPosition(get_absolute_position({70.f, 24.f}, AnchorPosition::TopLeft));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(score);

    sf::Text highscore_label(assets_manager.get_font());
    highscore_label.setString("HIGH SCORE");
    highscore_label.setFillColor(sf::Color::Red);
    highscore_label.setCharacterSize(24);
    sf::FloatRect highscore_label_bounds = highscore_label.getLocalBounds();
    highscore_label.setOrigin({highscore_label_bounds.size.x / 2.f, 0.f});
    highscore_label.setPosition(get_absolute_position({0.f, 0.f}, AnchorPosition::TopCenter));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(highscore_label);

    sf::Text highscore(assets_manager.get_font());
    highscore.setString(std::format("{:06d}", stage.get_player_data().get_highscore()));
    highscore.setCharacterSize(24);
    sf::FloatRect highscore_bounds = highscore.getLocalBounds();
    highscore.setOrigin({highscore_bounds.size.x / 2.f, 0.f});
    highscore.setPosition(get_absolute_position({0.f, 24.f}, AnchorPosition::TopCenter));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(highscore);

    sf::Sprite hammer_sprite(assets_manager.get_texture(AssetsManager::TextureId::Hammer));
    sf::FloatRect hammer_bounds = hammer_sprite.getLocalBounds();
    hammer_sprite.setOrigin({hammer_bounds.size.x / 2.f, hammer_bounds.size.y / 2.f});
    hammer_sprite.setPosition(get_absolute_position({30.f, 104.f}, AnchorPosition::TopLeft));
    hammer_sprite.setScale({2.f, 2.f});
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(hammer_sprite);

    sf::Text hammer_count(assets_manager.get_font());
    hammer_count.setString(std::format("{:d}", stage.get_player_data().get_hammer_use_count()));
    hammer_count.setCharacterSize(24);
    sf::FloatRect hammer_count_bounds = hammer_count.getLocalBounds();
    hammer_count.setOrigin({0.f, hammer_count_bounds.size.y / 2.f});
    hammer_count.setPosition(get_absolute_position({50.f, 110.f}, AnchorPosition::TopLeft));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(hammer_count);

    sf::Sprite barrel_sprite(assets_manager.get_texture(AssetsManager::TextureId::BarrelFront1));
    sf::FloatRect barrel_bounds = barrel_sprite.getLocalBounds();
    barrel_sprite.setOrigin({barrel_bounds.size.x / 2.f, barrel_bounds.size.y / 2.f});
    barrel_sprite.setPosition(get_absolute_position({30.f, 140.f}, AnchorPosition::TopLeft));
    barrel_sprite.setScale({2.f, 2.f});
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(barrel_sprite);

    sf::Text barrel_count(assets_manager.get_font());
    barrel_count.setString(std::format("{:d}", stage.get_player_data().get_jumped_over_barrels_count()));
    barrel_count.setCharacterSize(24);
    sf::FloatRect barrel_count_bounds = barrel_count.getLocalBounds();
    barrel_count.setOrigin({0.f, barrel_count_bounds.size.y / 2.f});
    barrel_count.setPosition(get_absolute_position({50.f, 140.f}, AnchorPosition::TopLeft));
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(barrel_count);

    int lives_count = stage.get_player_data().get_lives();
    for (int i = 0; i < lives_count; ++i) {
        sf::Sprite life_sprite(assets_manager.get_texture(AssetsManager::TextureId::JumpmanStill));
        life_sprite.setPosition(get_absolute_position({30.f + (i * 30.f), 80.f}, AnchorPosition::TopLeft));
        sf::FloatRect sprite_bounds = life_sprite.getLocalBounds();
        life_sprite.setOrigin({sprite_bounds.size.x / 2.f, sprite_bounds.size.y / 2.f});
        life_sprite.setScale({2.f, 2.f});
        layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(life_sprite);
    }

    sf::Text level_text(assets_manager.get_font());
    level_text.setString(std::format("L={:02d}", stage.get_player_data().get_level() + 1));
    level_text.setCharacterSize(24);
    sf::FloatRect level_text_bounds = level_text.getLocalBounds();
    level_text.setOrigin({level_text_bounds.size.x / 2.f, level_text_bounds.size.y / 2.f});
    level_text.setPosition(get_absolute_position({-100.f, 100.f}, AnchorPosition::TopRight));
    level_text.setFillColor(sf::Color::Blue);
    layer_stack.get_layer(LayerStack::LayerId::UI).add_to_layer(level_text);

    for (auto it = current_score_effects.begin(); it != current_score_effects.end(); ++it) {
        it->draw(layer_stack, assets_manager);
    }

    post_draw();
}

void StageView::update(float dt, Stage &stage) {
    for (auto it = current_score_effects.begin(); it != current_score_effects.end();) {
        if (!it->update(dt)) {
            it = current_score_effects.erase(it);
        } else {
            ++it;
        }
    }

    drawable_components.update_all(dt, stage);
}

void StageView::on_score_added(sf::Vector2f position, int score_to_add) { current_score_effects.emplace_back(position, score_to_add); }

void StageView::on_player_died() { current_score_effects.clear(); }
