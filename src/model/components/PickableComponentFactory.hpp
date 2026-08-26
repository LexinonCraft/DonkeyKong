#ifndef PICKABLE_COMPONENT_FACTORY_HPP
#define PICKABLE_COMPONENT_FACTORY_HPP

#include <memory>

#include "DK/model/components/Pickable.hpp"
#include "DK/model/util/AbstractComponentFactory.hpp"
#include "DK/model/util/Component.hpp"

class PickableComponentFactory : public AbstractComponentFactory<Component<Pickable>> {
protected:
    std::unique_ptr<Component<Pickable>> create_component_for(std::shared_ptr<BaseEntity> entity) override;
};

#endif
