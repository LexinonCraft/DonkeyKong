#ifndef UPDATABLE_COMPONENT_FACTORY_HPP
#define UPDATABLE_COMPONENT_FACTORY_HPP

#include <memory>

#include "../util/AbstractComponentFactory.hpp"
#include "../util/Component.hpp"
#include "Updatable.hpp"

class UpdatableComponentFactory : public AbstractComponentFactory<Component<Updatable>> {
protected:
    std::unique_ptr<Component<Updatable>> create_component_for(std::shared_ptr<BaseEntity> entity) override {
        return entity->create_updatable_component();
    }
};

#endif
