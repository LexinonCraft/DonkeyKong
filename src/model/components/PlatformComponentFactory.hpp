#ifndef PLATFORM_COMPONENT_FACTORY_H
#define PLATFORM_COMPONENT_FACTORY_H

#include <memory>

#include "../util/ComponentFactory.hpp"
#include "../util/Component.hpp"
#include "Platform.hpp"
#include "../entities/Barrel.hpp"
#include "../entities/Girder.hpp"

class PlatformComponentFactory : public ComponentFactory<Component<Platform>> {
protected:
    std::unique_ptr<Component<Platform>> create_component_for(Barrel &barrel, std::weak_ptr<Barrel> entity_ptr) const override {
        return nullptr;
    }

    std::unique_ptr<Component<Platform>> create_component_for(Girder &girder, std::weak_ptr<Girder> entity_ptr) const override {
        return std::make_unique<Component<Platform>>(entity_ptr);
    }
};

#endif
