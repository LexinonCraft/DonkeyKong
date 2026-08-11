#ifndef COMPONENT_FACTORY_HPP
#define COMPONENT_FACTORY_HPP

#include <memory>

#include "EntityVisitor.hpp"
#include "BaseEntity.hpp"

template <typename C>
class ComponentFactory : private EntityVisitor {
public:
    virtual ~ComponentFactory() {}

    std::unique_ptr<C> create_component_for(std::shared_ptr<BaseEntity> entity) {
        this->entity = entity;
        entity->accept(*this);
        return std::move(result);
    }

protected:
    virtual std::unique_ptr<C> create_component_for(Barrel &entity, std::shared_ptr<Barrel> entity_ptr) const {
        return nullptr;
    }
    virtual std::unique_ptr<C> create_component_for(Girder &entity, std::shared_ptr<Girder> entity_ptr) const {
        return nullptr;
    }
    virtual std::unique_ptr<C> create_component_for(Player &entity, std::shared_ptr<Player> entity_ptr) const {
        return nullptr;
    }
    virtual std::unique_ptr<C> create_component_for(Ladder &entity, std::shared_ptr<Ladder> entity_ptr) const {
        return nullptr;
    }

private:
    std::unique_ptr<C> result;
    std::shared_ptr<BaseEntity> entity;

    void visit(Barrel &barrel) override {
        result = create_component_for(barrel, std::dynamic_pointer_cast<Barrel>(entity));
    }
    void visit(Girder &girder) override {
        result = create_component_for(girder, std::dynamic_pointer_cast<Girder>(entity));
    }
    void visit(Player &player) override {
        result = create_component_for(player, std::dynamic_pointer_cast<Player>(entity));
    }
    void visit(Ladder &ladder) override {
        result = create_component_for(ladder, std::dynamic_pointer_cast<Ladder>(entity));
    }
};

#endif
