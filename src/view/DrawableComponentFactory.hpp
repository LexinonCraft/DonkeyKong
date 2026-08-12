#ifndef DRAWABLE_COMPONENT_FACTORY_HPP
#define DRAWABLE_COMPONENT_FACTORY_HPP

#include <memory>

#include "../model/util/AbstractComponentFactory.hpp"
#include "DrawableComponent.hpp"
#include "GirderRenderer.hpp"
#include "BarrelRenderer.hpp"
#include "PlayerRenderer.hpp"
#include "LadderRenderer.hpp"
#include "../model/entities/Barrel.hpp"
#include "../model/entities/Girder.hpp"
#include "../model/entities/Player.hpp"
#include "../model/entities/Ladder.hpp"

class DrawableComponentFactory : public AbstractComponentFactory<DrawableComponent>, private EntityVisitor {
public:
    std::unique_ptr<DrawableComponent> create_component_for(std::shared_ptr<BaseEntity> entity) override {
        entity->accept(*this);
        return std::move(component);
    }

private:
    std::unique_ptr<DrawableComponent> component;

    void visit(Barrel &barrel) override {
        component = std::make_unique<BarrelRenderer>(std::static_pointer_cast<Barrel>(barrel.shared_from_this()));
    }

    void visit(Girder &girder) override {
        component = std::make_unique<GirderRenderer>(std::static_pointer_cast<Girder>(girder.shared_from_this()));
    }

    void visit(Player &player) override {
        component = std::make_unique<PlayerRenderer>(std::static_pointer_cast<Player>(player.shared_from_this()));
    }

    void visit(Ladder &ladder) override {
        component = std::make_unique<LadderRenderer>(std::static_pointer_cast<Ladder>(ladder.shared_from_this()));
    }
};

#endif
