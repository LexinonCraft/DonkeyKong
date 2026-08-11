#ifndef COMPONENT_REPOSITORY_HPP
#define COMPONENT_REPOSITORY_HPP

#include <memory>
#include <unordered_map>

#include "EntityRepository.hpp"
#include "BaseEntity.hpp"
#include "ComponentFactory.hpp"

template <typename C>
class ComponentRepository : private EntityRepositoryObserver {
public:
    ComponentRepository(EntityRepository &entity_repo, std::unique_ptr<ComponentFactory<C>> component_factory) : entity_repo(entity_repo), observer_id(entity_repo.register_observer(*this)), component_factory(std::move(component_factory)) {
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

    auto begin() {
        return components.begin();
    }

    auto end() {
        return components.end();
    }

    std::weak_ptr<C> get_component_for_entity(Id entity_id) {
        auto it = components.find(entity_id);
        if (it != components.end()) {
            return std::weak_ptr<C>(it->second);
        }
        return std::weak_ptr<C>();
    }

private:
    std::unordered_map<Id, std::shared_ptr<C>> components;
    EntityRepository &entity_repo;
    const Id observer_id;
    std::unique_ptr<ComponentFactory<C>> component_factory;

    void on_entity_added(std::shared_ptr<BaseEntity> entity) override {
        auto component = component_factory->create_component_for(entity);
        if (component != nullptr) {
            components[entity->get_id()] = std::move(component);
        }
    }

    void on_entity_removed(std::shared_ptr<BaseEntity> entity) override {
        components.erase(entity->get_id());
    }
};

#endif
