#ifndef STAGE_SEQUENCE_HPP
#define STAGE_SEQUENCE_HPP

#include <memory>
#include <vector>

#include "DK/model/Declarations.hpp"

// This file contains the definition of the stage sequence for each level, as well as functions to advance stages and create stage
// instances.

/**
 * @brief Identifiers for the distinct stages in the game.
 */
enum class StageId {
    Stage25M,
    Stage100M,
};

/**
 * @brief Get the stage sequence for a specific level.
 *
 * @param level The level number.
 * @return A unique pointer to a vector containing the stage identifiers for the specified level.
 */
std::unique_ptr<std::vector<StageId>> get_stage_sequence(unsigned int level);

/**
 * @brief Get the number of stages in a specific level.
 *
 * @param level The level number.
 * @return The number of stages in the specified level.
 */
unsigned int get_number_of_stages_in_level(unsigned int level);

/**
 * @brief Get the stage identifier for a specific level and stage in level.
 *
 * @param level The level number.
 * @param stage_in_level The stage number within the level.
 * @return The stage identifier.
 */
StageId get_stage_id(unsigned int level, unsigned int stage_in_level);

/**
 * @brief Get the stage identifier for the current level and stage in level of the player data.
 *
 * @param player_data The player data containing the current level and stage in level.
 * @return The stage identifier.
 */
StageId get_stage_id(PlayerData &player_data);

/**
 * @brief Advance the player to the next stage according to the sequence.
 *
 * @param player_data The player data containing the current level and stage in level.
 */
void advance_stage(PlayerData &player_data);

/**
 * @brief Instantiate a stage based on the current level and stage in level of the player data.
 *
 * @param rng A random number generator function that returns an int.
 * @param player_data The player data containing the current level and stage in level.
 * @return The created stage instance.
 */
std::unique_ptr<Stage> create_stage(int rng(), PlayerData &player_data);

#endif
