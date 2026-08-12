#ifndef ENTITY_REPOSITORY_OBSERVER_HPP
#define ENTITY_REPOSITORY_OBSERVER_HPP

#include <memory>

#include "../Declarations.hpp"

/**
 * @brief Observer interface for entity creation and destruction events.
 *
 * Component repositories subscribe to this interface so they can keep their
 * component maps in sync with the repository contents.
 */
class EntityRepositoryObserver {
public:
    virtual ~EntityRepositoryObserver() {}

    /**
     * @brief Called when a new entity is inserted into the repository.
     * @param entity Entity that was added.
     */
    virtual void on_entity_added(std::shared_ptr<BaseEntity> entity) = 0;

    /**
     * @brief Called when an entity is scheduled for removal from the repository.
     * @param entity Entity that was removed.
     */
    virtual void on_entity_removed(std::shared_ptr<BaseEntity> entity) = 0;
};

#endif
