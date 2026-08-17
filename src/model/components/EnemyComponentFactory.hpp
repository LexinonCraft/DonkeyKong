#ifndef ENEMY_COMPONENT_FACTORY_HPP
#define ENEMY_COMPONENT_FACTORY_HPP

#include <memory>

#include "../util/AbstractComponentFactory.hpp"
#include "../util/Component.hpp"
#include "Enemy.hpp"

/**
 * @brief Factory that creates enemy components for entities that support enemies.
 */
class EnemyComponentFactory : public AbstractComponentFactory<Component<Enemy>> {
protected:
    /**
     * @brief Creates the enemy component for a specific entity if supported.
     * @param entity Entity to inspect.
     * @return Unique pointer to the enemy component or nullptr.
     */
    std::unique_ptr<Component<Enemy>> create_component_for(std::shared_ptr<BaseEntity> entity) override {
        return entity->create_enemy_component();
    }
};

#endif
