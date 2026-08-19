#include <stdexcept>

#include "StageSequence.hpp"
#include "stages/Stage100M.hpp"
#include "stages/Stage25M.hpp"
#include "PlayerData.hpp"

unsigned int get_number_of_stages_in_level(unsigned level) {
    // TODO
    return 2;
}

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

StageId get_stage_id(unsigned int level, unsigned int stage_in_level) {
    // TODO
    switch (stage_in_level) {
        case 0:
            return StageId::Stage25M;
        case 1:
            return StageId::Stage100M;
        default:
            throw std::logic_error("Unknown stage in level");
    }
}

StageId get_stage_id(PlayerData &player_data) {
    return get_stage_id(player_data.get_level(), player_data.get_stage_in_level());
}

std::unique_ptr<Stage> create_stage(Id id_generator(), PlayerData &player_data) {
    StageId stage_id = get_stage_id(player_data);
    // TODO
    switch (stage_id) {
        case StageId::Stage25M:
            return std::make_unique<Stage25M>(id_generator, player_data);
//        case StageId::Stage50M:
//            return std::make_unique<DemoStage2>(id_generator, player_data);
//        case StageId::Stage75M:
//            return std::make_unique<DemoStage>(id_generator, player_data);
        case StageId::Stage100M:
            return std::make_unique<Stage100M>(id_generator, player_data);
        default:
            throw std::logic_error("Unknown stage id");
    }
}
