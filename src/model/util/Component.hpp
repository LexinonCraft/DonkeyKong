#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <memory>
#include <utility>

/**
 * @brief Component that simply holds a reference to an entity.
 *
 * @tparam E Entity type this component belongs to.
 */
template <typename E> class Component {
public:
    /**
     * @brief Constructs a component for the given entity.
     * @param entity Entity instance referenced by this component.
     */
    explicit Component(std::shared_ptr<E> entity) : entity(std::move(entity)) {}

    virtual ~Component() = default;

    /**
     * @brief Returns the owning entity.
     * @returns Shared pointer to the entity behind this component.
     */
    std::shared_ptr<E> get_entity() const { return entity; }

private:
    std::shared_ptr<E> entity;
};

#endif
