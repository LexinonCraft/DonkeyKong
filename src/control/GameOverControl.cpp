#include "DK/control/GameOverControl.hpp"

#include "DK/model/PlayerData.hpp"

void GameOverControl::update(float dt) {
    time_elapsed += dt;
    if (time_elapsed >= 7.f) {
        player_data.reset();
        next_scene = NextScene::TitleScreen;
    }
}
