#ifndef ABSTRACT_COMPONENT_FACTORY_HPP
#define ABSTRACT_COMPONENT_FACTORY_HPP

#include <memory>

#include "DK/model/util/BaseEntity.hpp"

/**
 * @brief Abstract factory for creating component instances for a given entity.
 *
 * Concrete factories specialise this interface for each component type and
 * decide whether an entity should receive a component at all.
 *
 * @tparam C The component type created by the factory.
 */
template <typename C> class AbstractComponentFactory {
public:
    virtual ~AbstractComponentFactory() = default;

    /**
     * @brief Creates a component for the supplied entity.
     *
     * @param entity Entity to be associated with the resulting component.
     * @returns A component instance or nullptr when no component should be created.
     */
    virtual std::unique_ptr<C> create_component_for(std::shared_ptr<BaseEntity> entity) = 0;
};

#endif
