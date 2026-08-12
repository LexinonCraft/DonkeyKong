#ifndef COMPONENT_REPOSITORY_HPP
#define COMPONENT_REPOSITORY_HPP

#include <memory>
#include <unordered_map>

#include "EntityRepository.hpp"
#include "BaseEntity.hpp"
#include "AbstractComponentFactory.hpp"

/**
 * @brief Repository that keeps a component map synchronized with the entity repository.
 *
 * Each component repository subscribes to entity life-cycle events and builds or
 * removes the matching component instances as entities are created and deleted.
 *
 * @tparam C Concrete component type stored in this repository.
 */
template <typename C>
class ComponentRepository : private EntityRepositoryObserver {
public:
    /**
     * @brief Creates a component repository and populates it from the current entities.
     * @param entity_repo Repository whose entities are tracked.
     * @param component_factory Factory used to construct component instances.
     */
    ComponentRepository(EntityRepository &entity_repo, std::unique_ptr<AbstractComponentFactory<C>> component_factory) : entity_repo(entity_repo), observer_id(entity_repo.register_observer(*this)), component_factory(std::move(component_factory)) {
        for (auto it = entity_repo.begin(); it != entity_repo.end(); ++it) {
            std::shared_ptr<BaseEntity> entity = it->second;
            auto component = this->component_factory->create_component_for(entity);
            if (component != nullptr) {
                components[entity->get_id()] = std::move(component);
            }
        }
    }

    virtual ~ComponentRepository() {
        entity_repo.unregister_observer(observer_id);
    }

    /**
     * @brief Returns an iterator to the beginning of the component map.
     * @return Begin iterator.
     */
    auto begin() {
        return components.begin();
    }

    /**
     * @brief Returns an iterator to the end of the component map.
     * @return End iterator.
     */
    auto end() {
        return components.end();
    }

private:
    std::unordered_map<Id, std::shared_ptr<C>> components;
    EntityRepository &entity_repo;
    const Id observer_id;
    std::unique_ptr<AbstractComponentFactory<C>> component_factory;

    /**
     * @brief Adds a component for a newly inserted entity.
     * @param entity Added entity.
     */
    void on_entity_added(std::shared_ptr<BaseEntity> entity) override {
        auto component = component_factory->create_component_for(entity);
        if (component != nullptr) {
            components[entity->get_id()] = std::move(component);
        }
    }

    /**
     * @brief Removes the component for a deleted entity.
     * @param entity Removed entity.
     */
    void on_entity_removed(std::shared_ptr<BaseEntity> entity) override {
        components.erase(entity->get_id());
    }
};

#endif
