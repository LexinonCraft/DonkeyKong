#include "DK/model/PlayerData.hpp"

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

void PlayerData::set_level_and_stage_in_level(unsigned int new_level, unsigned int new_stage_in_level) {
    level = new_level;
    stage_in_level = new_stage_in_level;
}

void PlayerData::reset() {
    score = 0;
    // do not reset highscore
    lives = constants::INITIAL_LIVES;
    level = 0;
    stage_in_level = 0;
    jumped_over_barrels_count = 0;
    hammer_use_count = 0;
}
