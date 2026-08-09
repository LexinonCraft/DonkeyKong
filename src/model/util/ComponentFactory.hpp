#ifndef COMPONENT_FACTORY_H
#define COMPONENT_FACTORY_H

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
    virtual std::unique_ptr<C> create_component_for(Barrel &entity, std::weak_ptr<Barrel> entity_ptr) const = 0;
    virtual std::unique_ptr<C> create_component_for(Girder &entity, std::weak_ptr<Girder> entity_ptr) const = 0;

private:
    std::unique_ptr<C> result;
    std::weak_ptr<BaseEntity> entity;

    void visit(Barrel &barrel) override {
        result = create_component_for(barrel, std::dynamic_pointer_cast<Barrel>(entity.lock()));
    }
    void visit(Girder &girder) override {
        result = create_component_for(girder, std::dynamic_pointer_cast<Girder>(entity.lock()));
    }
};

#endif
