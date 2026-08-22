#ifndef ENEMY_COMPONENT_REPOSITORY_HPP
#define ENEMY_COMPONENT_REPOSITORY_HPP

#include <memory>

#include "DK/model/util/ComponentRepository.hpp"
#include "DK/model/util/Component.hpp"
#include "DK/model/components/EnemyComponentFactory.hpp"
#include "DK/model/components/Enemy.hpp"

/**
 * @brief Repository storing enemy behaviour components.
 *
 * It provides helper queries to find the enemy closest to
 * a player position when moving up or down.
 */
class EnemyComponentRepository : public ComponentRepository<Component<Enemy>> {
public:
    /**
     * @brief Creates the repository and registers it with the entity repository.
     * @param repository Entity repository to observe.
     */
    EnemyComponentRepository(EntityRepository &repository) : ComponentRepository<Component<Enemy>>(repository, std::make_unique<EnemyComponentFactory>()) {}

    std::shared_ptr<Enemy> find_touching_enemy(const sf::RectangleShape &player_shape);
};

#endif
