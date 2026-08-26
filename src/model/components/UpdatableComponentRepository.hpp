#ifndef UPDATABLE_COMPONENT_REPOSITORY_HPP
#define UPDATABLE_COMPONENT_REPOSITORY_HPP

#include <memory>

#include "DK/model/components/Updatable.hpp"
#include "DK/model/util/Component.hpp"
#include "DK/model/util/ComponentRepository.hpp"

/**
 * @brief Repository for all updatable entity behaviour components.
 */
class UpdatableComponentRepository : public ComponentRepository<Component<Updatable>> {
public:
    /**
     * @brief Creates the repository and subscribes it to the entity repository.
     * @param entity_repo Repository whose entities are tracked.
     */
    explicit UpdatableComponentRepository(EntityRepository &entity_repo);

    /**
     * @brief Calls update() on every tracked entity.
     * @param dt Time step in seconds.
     * @param level Level used to query surrounding game state.
     */
    void update_all(float dt, Stage &level);
};

#endif
