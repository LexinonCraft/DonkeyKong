#ifndef ABSTRACT_COMPONENT_FACTORY_HPP
#define ABSTRACT_COMPONENT_FACTORY_HPP

#include <memory>

#include "BaseEntity.hpp"

template <typename C>
class AbstractComponentFactory {
public:
    virtual ~AbstractComponentFactory() = default;

    virtual std::unique_ptr<C> create_component_for(std::shared_ptr<BaseEntity> entity) = 0;
};

#endif
