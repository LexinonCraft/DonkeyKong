#ifndef PLAYER_DATA_HPP
#define PLAYER_DATA_HPP

#include "../Constants.hpp"

class PlayerData {
public:
    unsigned int get_score() const { return score; }
    unsigned int get_highscore() const { return highscore; }
    unsigned int get_lives() const { return lives; }
    unsigned int get_level() const { return level; }
    unsigned int get_stage_in_level() const { return stage_in_level; }
    unsigned int get_jumped_over_barrels_count() const { return jumped_over_barrels_count; }
    unsigned int get_hammer_use_count() const { return hammer_use_count; }

    void add_to_score(unsigned int points);

    bool lose_life();

    void set_level_and_stage_in_level(unsigned int new_level, unsigned int new_stage_in_level);

    void increment_jumped_over_barrels_count() { jumped_over_barrels_count++; }
    void increment_hammer_use_count() { hammer_use_count++; }

    void reset();

private:
    unsigned int score = 0;
    unsigned int highscore = 0;
    unsigned int lives = constants::INITIAL_LIVES;
    unsigned int level = 0;
    unsigned int stage_in_level = 0;
    unsigned int jumped_over_barrels_count = 0;
    unsigned int hammer_use_count = 0;
};

#endif
