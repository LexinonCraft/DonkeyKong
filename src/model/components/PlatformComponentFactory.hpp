#ifndef PLATFORM_COMPONENT_FACTORY_HPP
#define PLATFORM_COMPONENT_FACTORY_HPP

#include <memory>

#include "../util/AbstractComponentFactory.hpp"
#include "../util/Component.hpp"
#include "Platform.hpp"

class PlatformComponentFactory : public AbstractComponentFactory<Component<Platform>> {
protected:
    std::unique_ptr<Component<Platform>> create_component_for(std::shared_ptr<BaseEntity> entity) override {
        return entity->create_platform_component();
    }
};

#endif
