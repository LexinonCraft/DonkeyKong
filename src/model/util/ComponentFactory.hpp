#ifndef COMPONENT_FACTORY_HPP
#define COMPONENT_FACTORY_HPP

#include <memory>

#include "EntityVisitor.hpp"
#include "BaseEntity.hpp"

template <typename C>
class ComponentFactory : private EntityVisitor {
public:
    virtual ~ComponentFactory() {}

    std::unique_ptr<C> create_component_for(std::weak_ptr<BaseEntity> entity) {
        this->entity = entity;
        entity.lock()->accept(*this);
        return std::move(result);
    }

protected:
    virtual std::unique_ptr<C> create_component_for(Barrel &entity, std::weak_ptr<Barrel> entity_ptr) const {
        return nullptr;
    }
    virtual std::unique_ptr<C> create_component_for(Girder &entity, std::weak_ptr<Girder> entity_ptr) const {
        return nullptr;
    }
    virtual std::unique_ptr<C> create_component_for(Player &entity, std::weak_ptr<Player> entity_ptr) const {
        return nullptr;
    }
    virtual std::unique_ptr<C> create_component_for(Ladder &entity, std::weak_ptr<Ladder> entity_ptr) const {
        return nullptr;
    }

private:
    std::unique_ptr<C> result;
    std::weak_ptr<BaseEntity> entity;

    void visit(Barrel &barrel) override {
        result = create_component_for(barrel, std::dynamic_pointer_cast<Barrel>(entity.lock()));
    }
    void visit(Girder &girder) override {
        result = create_component_for(girder, std::dynamic_pointer_cast<Girder>(entity.lock()));
    }
    void visit(Player &player) override {
        result = create_component_for(player, std::dynamic_pointer_cast<Player>(entity.lock()));
    }
    void visit(Ladder &ladder) override {
        result = create_component_for(ladder, std::dynamic_pointer_cast<Ladder>(entity.lock()));
    }
};

#endif
