#include "JumpableComponentRepository.hpp"

void JumpableComponentRepository::check_all_jumpables(sf::Vector2f player_position, Stage &stage) {
    for (auto it = begin(); it != end(); ++it) {
        it->second->get_entity()->check_jumps_over(player_position, stage);
    }
}