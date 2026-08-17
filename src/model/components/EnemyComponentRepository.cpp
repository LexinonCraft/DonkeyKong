#include "EnemyComponentRepository.hpp"

std::shared_ptr<Enemy> EnemyComponentRepository::find_touching_enemy(const sf::RectangleShape &player_shape) {
    for (auto it = begin(); it != end(); ++it) {
        auto enemy = it->second->get_entity();
        if (enemy->touches(player_shape)) {
            return enemy;
        }
    }
    return nullptr;
}
