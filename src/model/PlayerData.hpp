#ifndef PLAYER_DATA_HPP
#define PLAYER_DATA_HPP

#include "Constants.hpp"
#include "Stage.hpp"

class PlayerData {
public:
    PlayerData() : score(0), highscore(0), lives(constants::INITIAL_LIVES), level(0), stage(Stage::StageId::Stage25M) {}

    unsigned int get_score() const { return score; }
    unsigned int get_highscore() const { return highscore; }
    unsigned int get_lives() const { return lives; }
    unsigned int get_level() const { return level; }
    Stage::StageId get_stage() const { return stage; }

    void add_to_score(unsigned int points);

    bool lose_life();

    void set_level_and_stage(unsigned int new_level, Stage::StageId new_stage);

private:
    unsigned int score;
    unsigned int highscore;
    unsigned int lives;
    unsigned int level;
    Stage::StageId stage;
};

#endif
