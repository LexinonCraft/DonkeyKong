#ifndef ENTITY_REPOSITORY_OBSERVER_HPP
#define ENTITY_REPOSITORY_OBSERVER_HPP

#include <memory>

#include "../Declarations.hpp"

class EntityRepositoryObserver {
public:
    virtual ~EntityRepositoryObserver() {}

    virtual void on_entity_added(std::weak_ptr<BaseEntity> entity) = 0;

    virtual void on_entity_removed(std::weak_ptr<BaseEntity> entity) = 0;
};

#endif
