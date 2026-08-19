#ifndef PLAYER_DATA_HPP
#define PLAYER_DATA_HPP

#include "../Constants.hpp"

class PlayerData {
public:
    PlayerData() : score(0), highscore(0), lives(constants::INITIAL_LIVES), level(0), stage_in_level(0) {}

    unsigned int get_score() const { return score; }
    unsigned int get_highscore() const { return highscore; }
    unsigned int get_lives() const { return lives; }
    unsigned int get_level() const { return level; }
    unsigned int get_stage_in_level() const { return stage_in_level; }

    void add_to_score(unsigned int points);

    bool lose_life();

    void set_level_and_stage_in_level(unsigned int new_level, unsigned int new_stage_in_level);

    void reset();

private:
    unsigned int score;
    unsigned int highscore;
    unsigned int lives;
    unsigned int level;
    unsigned int stage_in_level;
};

#endif
