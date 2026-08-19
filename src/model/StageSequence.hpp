#ifndef STAGE_SEQUENCE_HPP
#define STAGE_SEQUENCE_HPP

#include <memory>

#include "Declarations.hpp"

enum class StageId {
    Stage25M,
//    Stage50M,
//    Stage75M,
    Stage100M,
};

unsigned int get_number_of_stages_in_level(unsigned level);

void advance_stage(PlayerData &player_data);

StageId get_stage_id(unsigned int level, unsigned int stage_in_level);
StageId get_stage_id(PlayerData &player_data);

std::unique_ptr<Stage> create_stage(Id id_generator(), PlayerData &player_data);

#endif
