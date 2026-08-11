#ifndef UPDATABLE_COMPONENT_FACTORY_HPP
#define UPDATABLE_COMPONENT_FACTORY_HPP

#include <memory>

#include "../util/ComponentFactory.hpp"
#include "../util/Component.hpp"
#include "Updatable.hpp"
#include "../entities/Barrel.hpp"

class UpdatableComponentFactory : public ComponentFactory<Component<Updatable>> {
protected:
    std::unique_ptr<Component<Updatable>> create_component_for(Barrel &barrel, std::weak_ptr<Barrel> entity_ptr) const override {
        return std::make_unique<Component<Updatable>>(entity_ptr);
    }

    std::unique_ptr<Component<Updatable>> create_component_for(Girder &girder, std::weak_ptr<Girder> entity_ptr) const override {
        return nullptr;
    }
};

#endif
