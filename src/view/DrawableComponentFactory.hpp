#ifndef DRAWABLE_COMPONENT_FACTORY_H
#define DRAWABLE_COMPONENT_FACTORY_H

#include <memory>

#include "../model/util/ComponentFactory.hpp"
#include "DrawableComponent.hpp"
#include "GirderRenderer.hpp"
#include "BarrelRenderer.hpp"
#include "../model/entities/Barrel.hpp"
#include "../model/entities/Girder.hpp"

class DrawableComponentFactory : public ComponentFactory<DrawableComponent> {
protected:
    std::unique_ptr<DrawableComponent> create_component_for(Barrel &barrel, std::weak_ptr<Barrel> entity_ptr) const override {
        return std::make_unique<BarrelRenderer>(entity_ptr);
    }

    std::unique_ptr<DrawableComponent> create_component_for(Girder &girder, std::weak_ptr<Girder> entity_ptr) const override {
        return std::make_unique<GirderRenderer>(entity_ptr);
    }
};

#endif
