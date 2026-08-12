#ifndef UPDATABLE_COMPONENT_FACTORY_HPP
#define UPDATABLE_COMPONENT_FACTORY_HPP

#include <memory>

#include "../util/AbstractComponentFactory.hpp"
#include "../util/Component.hpp"
#include "Updatable.hpp"

/**
 * @brief Factory that creates update behaviour components for entities that move or animate.
 */
class UpdatableComponentFactory : public AbstractComponentFactory<Component<Updatable>> {
protected:
    /**
     * @brief Creates the updatable component for a specific entity if supported.
     * @param entity Entity to inspect.
     * @return Unique pointer to the updatable component or nullptr.
     */
    std::unique_ptr<Component<Updatable>> create_component_for(std::shared_ptr<BaseEntity> entity) override {
        return entity->create_updatable_component();
    }
};

#endif
