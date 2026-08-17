#ifndef STAGE_SEQUENCE_HPP
#define STAGE_SEQUENCE_HPP

#include <memory>

#include "Declarations.hpp"

enum class StageId {
    Stage25M,
    Stage50M,
    Stage75M,
    Stage100M,
};

void advance_stage_id(PlayerData &player_data);

std::unique_ptr<Stage> create_stage(Id id_generator(), PlayerData &player_data);

#endif
