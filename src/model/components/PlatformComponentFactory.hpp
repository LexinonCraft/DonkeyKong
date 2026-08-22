#ifndef PLATFORM_COMPONENT_FACTORY_HPP
#define PLATFORM_COMPONENT_FACTORY_HPP

#include <memory>

#include "DK/model/util/AbstractComponentFactory.hpp"
#include "DK/model/util/Component.hpp"
#include "DK/model/components/Platform.hpp"

/**
 * @brief Factory that creates platform components for entities that behave like surfaces.
 */
class PlatformComponentFactory : public AbstractComponentFactory<Component<Platform>> {
protected:
    /**
     * @brief Creates the platform component for a specific entity if supported.
     * @param entity Entity to inspect.
     * @return Unique pointer to the platform component or nullptr.
     */
    std::unique_ptr<Component<Platform>> create_component_for(std::shared_ptr<BaseEntity> entity) override {
        return entity->create_platform_component();
    }
};

#endif
