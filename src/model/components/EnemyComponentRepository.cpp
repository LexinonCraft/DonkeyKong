#include "DK/model/components/EnemyComponentRepository.hpp"

#include "DK/model/components/EnemyComponentFactory.hpp"

std::unique_ptr<Component<Enemy>> EnemyComponentFactory::create_component_for(std::shared_ptr<BaseEntity> entity) {
    return entity->create_enemy_component();
}

EnemyComponentRepository::EnemyComponentRepository(EntityRepository &repository)
    : ComponentRepository<Component<Enemy>>(repository, std::make_unique<EnemyComponentFactory>()) {}

std::shared_ptr<Enemy> EnemyComponentRepository::find_touching_enemy(const sf::RectangleShape &player_shape) {
    for (auto it = begin(); it != end(); ++it) {
        auto enemy = it->second->get_entity();
        if (enemy->touches(player_shape)) {
            return enemy;
        }
    }
    return nullptr;
}
