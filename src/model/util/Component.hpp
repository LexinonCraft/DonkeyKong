#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <memory>

template <typename E>
class Component {
public:
    Component(std::shared_ptr<E> entity) : entity(entity) {}

    virtual ~Component() {}

    std::shared_ptr<E> get_entity() const {
        return entity;
    }

private:
    std::shared_ptr<E> entity;
};

#endif
