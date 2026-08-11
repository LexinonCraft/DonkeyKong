#ifndef DRAWABLE_COMPONENT_FACTORY_HPP
#define DRAWABLE_COMPONENT_FACTORY_HPP

#include <memory>

#include "../model/util/ComponentFactory.hpp"
#include "DrawableComponent.hpp"
#include "GirderRenderer.hpp"
#include "BarrelRenderer.hpp"
#include "PlayerRenderer.hpp"
#include "LadderRenderer.hpp"
#include "../model/entities/Barrel.hpp"
#include "../model/entities/Girder.hpp"
#include "../model/entities/Player.hpp"
#include "../model/entities/Ladder.hpp"

class DrawableComponentFactory : public ComponentFactory<DrawableComponent> {
protected:
    std::unique_ptr<DrawableComponent> create_component_for(Barrel &barrel, std::shared_ptr<Barrel> entity_ptr) const override {
        return std::make_unique<BarrelRenderer>(entity_ptr);
    }

    std::unique_ptr<DrawableComponent> create_component_for(Girder &girder, std::shared_ptr<Girder> entity_ptr) const override {
        return std::make_unique<GirderRenderer>(entity_ptr);
    }

    std::unique_ptr<DrawableComponent> create_component_for(Player &entity, std::shared_ptr<Player> entity_ptr) const override {
        return std::make_unique<PlayerRenderer>(entity_ptr);
    }

    std::unique_ptr<DrawableComponent> create_component_for(Ladder &entity, std::shared_ptr<Ladder> entity_ptr) const override {
        return std::make_unique<LadderRenderer>(entity_ptr);
    }
};

#endif
