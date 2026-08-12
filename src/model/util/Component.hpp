#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <memory>

/**
 * @brief Thin wrapper that stores a pointer to the entity owning the component.
 *
 * This acts as the component-side handle back to the entity while keeping the
 * actual entity logic in the concrete entity classes.
 *
 * @tparam E Entity type this component belongs to.
 */
template <typename E>
class Component {
public:
    /**
     * @brief Constructs a component for the given entity.
     * @param entity Entity instance referenced by this component.
     */
    Component(std::shared_ptr<E> entity) : entity(entity) {}

    virtual ~Component() {}

    /**
     * @brief Returns the owning entity.
     * @return Shared pointer to the entity behind this component.
     */
    std::shared_ptr<E> get_entity() const {
        return entity;
    }

private:
    std::shared_ptr<E> entity;
};

#endif
