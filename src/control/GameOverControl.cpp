#include "DK/control/GameOverControl.hpp"

#include "DK/Constants.hpp"
#include "DK/model/PlayerData.hpp"

void GameOverControl::update(float dt) {
    time_elapsed += dt;
    if (time_elapsed >= constants::GAME_OVER_DURATION) {
        player_data.reset();
        next_scene = NextScene::TitleScreen;
    }
}
