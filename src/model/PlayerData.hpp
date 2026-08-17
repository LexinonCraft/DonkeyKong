#ifndef PLAYER_DATA_HPP
#define PLAYER_DATA_HPP

#include "../Constants.hpp"
#include "StageSequence.hpp"

class PlayerData {
public:
    PlayerData() : score(0), highscore(0), lives(constants::INITIAL_LIVES), level(0), stage(StageId::Stage25M) {}

    unsigned int get_score() const { return score; }
    unsigned int get_highscore() const { return highscore; }
    unsigned int get_lives() const { return lives; }
    unsigned int get_level() const { return level; }
    StageId get_stage() const { return stage; }

    void add_to_score(unsigned int points);

    bool lose_life();

    void set_level_and_stage(unsigned int new_level, StageId new_stage);

    void reset();

private:
    unsigned int score;
    unsigned int highscore;
    unsigned int lives;
    unsigned int level;
    StageId stage;
};

#endif
