#ifndef CLIMBABLE_COMPONENT_FACTORY_HPP
#define CLIMBABLE_COMPONENT_FACTORY_HPP

#include <memory>

#include "../util/ComponentFactory.hpp"
#include "../util/Component.hpp"
#include "Climbable.hpp"
#include "../entities/Ladder.hpp"

class ClimbableComponentFactory : public ComponentFactory<Component<Climbable>> {
protected:
    std::unique_ptr<Component<Climbable>> create_component_for(Ladder &ladder, std::shared_ptr<Ladder> entity_ptr) const override {
        return std::make_unique<Component<Climbable>>(entity_ptr);
    }
};

#endif
