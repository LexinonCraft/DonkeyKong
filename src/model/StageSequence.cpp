#include "DK/model/StageSequence.hpp"

#include <stdexcept>

#include "DK/model/PlayerData.hpp"
#include "DK/model/stages/Stage100M.hpp"
#include "DK/model/stages/Stage25M.hpp"

std::unique_ptr<std::vector<StageId>> get_stage_sequence(unsigned int level) {
    auto stage_sequence = std::make_unique<std::vector<StageId>>();
    stage_sequence->push_back(StageId::Stage25M);
    stage_sequence->push_back(StageId::Stage100M);
    return stage_sequence;
    // currently, all levels have the same stage sequence. This can be modified in the future to have different sequences for different
    // levels.
}

unsigned int get_number_of_stages_in_level(unsigned int level) { return get_stage_sequence(level)->size(); }

StageId get_stage_id(unsigned int level, unsigned int stage_in_level) { return get_stage_sequence(level)->at(stage_in_level); }

StageId get_stage_id(PlayerData &player_data) { return get_stage_id(player_data.get_level(), player_data.get_stage_in_level()); }

void advance_stage(PlayerData &player_data) {
    unsigned int current_stage_in_level = player_data.get_stage_in_level();
    unsigned int current_level = player_data.get_level();
    unsigned int number_of_stages_in_level = get_number_of_stages_in_level(current_level);

    if (current_stage_in_level + 1 < number_of_stages_in_level) {
        player_data.set_level_and_stage_in_level(current_level, current_stage_in_level + 1);
    } else {
        player_data.set_level_and_stage_in_level(current_level + 1, 0);
    }
}

std::unique_ptr<Stage> create_stage(int rng(), PlayerData &player_data) {
    switch (get_stage_id(player_data)) {
        case StageId::Stage25M:
            return std::make_unique<Stage25M>(rng, player_data);
        case StageId::Stage100M:
            return std::make_unique<Stage100M>(rng, player_data);
        default:
            throw std::logic_error("Unknown stage id");
    }
}
