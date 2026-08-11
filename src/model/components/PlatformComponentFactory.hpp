#ifndef PLATFORM_COMPONENT_FACTORY_HPP
#define PLATFORM_COMPONENT_FACTORY_HPP

#include <memory>

#include "../util/ComponentFactory.hpp"
#include "../util/Component.hpp"
#include "Platform.hpp"
#include "../entities/Girder.hpp"

class PlatformComponentFactory : public ComponentFactory<Component<Platform>> {
protected:
    std::unique_ptr<Component<Platform>> create_component_for(Girder &girder, std::shared_ptr<Girder> entity_ptr) const override {
        return std::make_unique<Component<Platform>>(entity_ptr);
    }
};

#endif
