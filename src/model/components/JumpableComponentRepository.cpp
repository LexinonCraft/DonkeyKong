#include "DK/model/components/JumpableComponentRepository.hpp"

void JumpableComponentRepository::check_all_jumpables(const Player &player, Stage &stage) {
    for (auto it = begin(); it != end(); ++it) {
        it->second->get_entity()->check_jumps_over(player, stage);
    }
}
