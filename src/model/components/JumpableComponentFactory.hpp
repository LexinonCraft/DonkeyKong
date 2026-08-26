#ifndef JUMPABLE_COMPONENT_FACTORY_HPP
#define JUMPABLE_COMPONENT_FACTORY_HPP

#include <memory>

#include "DK/model/components/Jumpable.hpp"
#include "DK/model/util/AbstractComponentFactory.hpp"
#include "DK/model/util/Component.hpp"

class JumpableComponentFactory : public AbstractComponentFactory<Component<Jumpable>> {
protected:
    /**
     * @brief Creates the jumpable component for a specific entity if supported.
     * @param entity Entity to inspect.
     * @returns Unique pointer to the jumpable component or nullptr.
     */
    std::unique_ptr<Component<Jumpable>> create_component_for(std::shared_ptr<BaseEntity> entity) override;
};

#endif
