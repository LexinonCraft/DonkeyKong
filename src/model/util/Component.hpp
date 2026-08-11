#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <memory>

template <typename E>
class Component {
public:
    Component(std::weak_ptr<E> entity) : entity(entity) {}

    virtual ~Component() {}

    std::weak_ptr<E> get_entity() const {
        return entity;
    }

    std::shared_ptr<E> get_entity_locked() const {
        return entity.lock();
    }

private:
    std::weak_ptr<E> entity;
};

#endif
