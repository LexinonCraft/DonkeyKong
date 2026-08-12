#ifndef CLIMBABLE_COMPONENT_FACTORY_HPP
#define CLIMBABLE_COMPONENT_FACTORY_HPP

#include <memory>

#include "../util/AbstractComponentFactory.hpp"
#include "../util/Component.hpp"
#include "Climbable.hpp"

class ClimbableComponentFactory : public AbstractComponentFactory<Component<Climbable>> {
protected:
    std::unique_ptr<Component<Climbable>> create_component_for(std::shared_ptr<BaseEntity> entity) override {
        return entity->create_climbable_component();
    }
};

#endif
