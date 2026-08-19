#include <stdexcept>

#include "StageSequence.hpp"
#include "stages/Stage100M.hpp"
#include "DemoStage.hpp"
#include "DemoStage2.hpp"
#include "PlayerData.hpp"

void advance_stage_id(PlayerData &player_data) {
    // TODO
    switch (player_data.get_stage()) {
        case StageId::Stage25M:
            player_data.set_level_and_stage(player_data.get_level(), StageId::Stage50M);
            break;
        case StageId::Stage50M:
            player_data.set_level_and_stage(player_data.get_level(), StageId::Stage75M);
            break;
        case StageId::Stage75M:
            player_data.set_level_and_stage(player_data.get_level(), StageId::Stage100M);
            break;
        case StageId::Stage100M:
            player_data.set_level_and_stage(player_data.get_level() + 1, StageId::Stage25M);
            break;
    }
}

std::unique_ptr<Stage> create_stage(Id id_generator(), PlayerData &player_data) {
    StageId stage_id = player_data.get_stage();
    // TODO
    switch (stage_id) {
        case StageId::Stage25M:
            return std::make_unique<Stage100M>(id_generator, player_data);
        case StageId::Stage50M:
            return std::make_unique<DemoStage2>(id_generator, player_data);
        case StageId::Stage75M:
            return std::make_unique<DemoStage>(id_generator, player_data);
        case StageId::Stage100M:
            return std::make_unique<DemoStage>(id_generator, player_data);
        default:
            throw std::logic_error("Unknown stage id");
    }
}
