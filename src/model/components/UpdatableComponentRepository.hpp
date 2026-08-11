#ifndef UPDATABLE_COMPONENT_REPOSITORY_HPP
#define UPDATABLE_COMPONENT_REPOSITORY_HPP

#include <memory>

#include "../util/ComponentRepository.hpp"
#include "../util/Component.hpp"
#include "UpdatableComponentFactory.hpp"
#include "Updatable.hpp"

class UpdatableComponentRepository : public ComponentRepository<Component<Updatable>> {
public:
    UpdatableComponentRepository(EntityRepository &entity_repo) : ComponentRepository<Component<Updatable>>(entity_repo, std::make_unique<UpdatableComponentFactory>()) {}

    void update_all(float dt, Level &level) {
        for (auto it = begin(); it != end(); ++it) {
            it->second->get_entity_locked()->update(dt, level);
        }
    }
};

#endif
