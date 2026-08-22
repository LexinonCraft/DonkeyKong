#ifndef JUMPABLE_COMPONENT_REPOSITORY_HPP
#define JUMPABLE_COMPONENT_REPOSITORY_HPP

#include <memory>

#include "DK/model/util/ComponentRepository.hpp"
#include "DK/model/util/Component.hpp"
#include "DK/model/components/JumpableComponentFactory.hpp"
#include "DK/model/components/Jumpable.hpp"

/**
 * @brief Repository for all jumpable entity behaviour components.
 */
class JumpableComponentRepository : public ComponentRepository<Component<Jumpable>> {
public:
    /**
     * @brief Creates the repository and subscribes it to the entity repository.
     * @param entity_repo Repository whose entities are tracked.
     */
    JumpableComponentRepository(EntityRepository &entity_repo) : ComponentRepository<Component<Jumpable>>(entity_repo, std::make_unique<JumpableComponentFactory>()) {}

    void check_all_jumpables(const Player &player, Stage &stage);
};

#endif
