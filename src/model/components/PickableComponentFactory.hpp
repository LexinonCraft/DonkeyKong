#ifndef PICKABLE_COMPONENT_FACTORY_HPP
#define PICKABLE_COMPONENT_FACTORY_HPP

#include <memory>

#include "../util/AbstractComponentFactory.hpp"
#include "../util/Component.hpp"
#include "Pickable.hpp"

class PickableComponentFactory : public AbstractComponentFactory<Component<Pickable>> {
protected:
    std::unique_ptr<Component<Pickable>> create_component_for(std::shared_ptr<BaseEntity> entity) override {
        return entity->create_pickable_component();
    }
};

#endif
