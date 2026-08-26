#ifndef CLIMBABLE_COMPONENT_FACTORY_HPP
#define CLIMBABLE_COMPONENT_FACTORY_HPP

#include <memory>

#include "DK/model/components/Climbable.hpp"
#include "DK/model/util/AbstractComponentFactory.hpp"
#include "DK/model/util/Component.hpp"

/**
 * @brief Factory that creates climbable components for entities that support climbing.
 */
class ClimbableComponentFactory : public AbstractComponentFactory<Component<Climbable>> {
protected:
    /**
     * @brief Creates the climbable component for a specific entity if supported.
     * @param entity Entity to inspect.
     * @returns Unique pointer to the climbable component or nullptr.
     */
    std::unique_ptr<Component<Climbable>> create_component_for(std::shared_ptr<BaseEntity> entity) override;
};

#endif
