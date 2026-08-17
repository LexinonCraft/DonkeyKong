#include "PlayerData.hpp"

void PlayerData::add_to_score(unsigned int points) {
    score += points;
    if (score > highscore) {
        highscore = score;
    }
}

bool PlayerData::lose_life() {
    --lives;
    return lives > 0;
}

void PlayerData::set_level_and_stage(unsigned int new_level, StageId new_stage) {
    level = new_level;
    stage = new_stage;
}

void PlayerData::reset() {
    score = 0;
    // do not reset highscore
    lives = constants::INITIAL_LIVES;
    level = 0;
    stage = StageId::Stage25M;
}
