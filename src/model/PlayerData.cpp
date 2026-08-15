#include "PlayerData.hpp"

void PlayerData::add_to_score(unsigned int points) {
    score += points;
    if (score > highscore) {
        highscore = score;
    }
}

bool PlayerData::lose_life() {
    if (lives > 0) {
        --lives;
        return true;
    }
    return false;
}

void PlayerData::set_level_and_stage(unsigned int new_level, Stage::StageId new_stage) {
    level = new_level;
    stage = new_stage;
}
