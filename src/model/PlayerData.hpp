#ifndef PLAYER_DATA_HPP
#define PLAYER_DATA_HPP

#include "DK/Constants.hpp"

/**
 * @brief Stores and manages player-related data such as score, lives, and progress.
 */
class PlayerData {
public:
    /** @returns The current score. */
    unsigned int get_score() const { return score; }

    /** @returns The highscore. */
    unsigned int get_highscore() const { return highscore; }

    /** @returns The number of lives remaining. */
    unsigned int get_lives() const { return lives; }

    /** @returns The current level (0-indexed). */
    unsigned int get_level() const { return level; }

    /** @returns The index of the current stage within the level (0-indexed). */
    unsigned int get_stage_in_level() const { return stage_in_level; }
    /** @returns The number of barrels the player has jumped over. */
    unsigned int get_jumped_over_barrels_count() const { return jumped_over_barrels_count; }

    /** @returns The number of times the player has used the hammer. */
    unsigned int get_hammer_use_count() const { return hammer_use_count; }

    /** @brief Adds points to the player's score and updates the highscore if necessary. */
    void add_to_score(unsigned int points);

    /**
     * @brief Removes a life from the player.
     *
     * @returns true if the player still has lives remaining after losing one.
     * @returns false otherwise
     */
    bool lose_life();

    /** @brief Sets the current level and stage within the level. */
    void set_level_and_stage_in_level(unsigned int new_level, unsigned int new_stage_in_level);

    /** @brief Increments the number of barrels the player has jumped over. */
    void increment_jumped_over_barrels_count() { jumped_over_barrels_count++; }

    /** @brief Increments the number of times the player has used the hammer. */
    void increment_hammer_use_count() { hammer_use_count++; }

    /** @brief Resets the player data to its initial state, except for the highscore. */
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
