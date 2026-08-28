#ifndef GAME_OVER_CONTROL_HPP
#define GAME_OVER_CONTROL_HPP

#include <optional>

#include "DK/control/AbstractSceneControl.hpp"
#include "DK/model/Declarations.hpp"
#include "DK/view/Declarations.hpp"
#include "DK/view/views/GameOverView.hpp"

/**
 * @brief Control class for the game over screen. It is also responsible for resetting the player data.
 *
 */
class GameOverControl : public AbstractSceneControl {
public:
    GameOverControl(sf::RenderWindow &window, PlayerData &player_data, AssetsManager &assets_manager)
        : AbstractSceneControl(window), player_data(player_data) {
        game_over_view.emplace(window, assets_manager, player_data);
    }

    GameOverControl(PlayerData &player_data) : AbstractSceneControl(), player_data(player_data) {}

    void handle_event(sf::Event *event) override {}

    void handle_input() override {}

    void update(float dt) override;

    void draw() override {
        if (game_over_view.has_value()) {
            game_over_view->draw();
        }
    }

    NextScene get_next_scene() const override { return next_scene; }

private:
    std::optional<GameOverView> game_over_view;
    NextScene next_scene = NextScene::Stay;
    float time_elapsed = 0.f;
    PlayerData &player_data;
};

#endif
