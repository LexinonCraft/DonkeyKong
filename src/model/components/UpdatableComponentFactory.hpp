#ifndef UPDATABLE_COMPONENT_FACTORY_HPP
#define UPDATABLE_COMPONENT_FACTORY_HPP

#include <memory>

#include "DK/model/components/Updatable.hpp"
#include "DK/model/util/AbstractComponentFactory.hpp"
#include "DK/model/util/Component.hpp"

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
