#ifndef ENTITY_REPOSITORY_HPP
#define ENTITY_REPOSITORY_HPP

#include <SFML/System/Vector2.hpp>
#include <memory>
#include <unordered_map>

#include "../Declarations.hpp"
#include "EntityRepositoryObserver.hpp"
#include "BaseEntity.hpp"
#include "../entities/Barrel.hpp"
#include "../entities/Girder.hpp"
#include "../entities/Player.hpp"
#include "../entities/Ladder.hpp"
#include "Ref.hpp"

class EntityRepository {
public:
    EntityRepository(Id (*id_generator)()) : id_generator(id_generator) {}

    std::weak_ptr<Barrel> add_barrel(sf::Vector2f position) {
        return add_entity(std::make_shared<Barrel>(gen_ref(), position));
    }

    std::weak_ptr<Girder> add_girder(sf::Vector2f left, sf::Vector2f right) {
        return add_entity(std::make_shared<Girder>(gen_ref(), left, right));
    }

    std::weak_ptr<Player> add_player() {
        return add_entity(std::make_shared<Player>(gen_ref()));
    }

    std::weak_ptr<Ladder> add_ladder(std::weak_ptr<Platform> lower_end, std::weak_ptr<Platform> upper_end, float x_position) {
        return add_entity(std::make_shared<Ladder>(gen_ref(), lower_end, upper_end, x_position));
    }

    bool remove_entity(std::weak_ptr<BaseEntity> entity) {
        if (entity.expired()) {
            return false;
        }

        for (auto it = observers.begin(); it != observers.end(); ++it) {
            it->second->on_entity_removed(entity);
        }

        entities.erase(entity.lock()->get_id());

        return true;
    }

    auto begin() {
        return entities.begin();
    }

    auto end() {
        return entities.end();
    }

    Id register_observer(EntityRepositoryObserver &observer) {
        Id id = id_generator();
        observers[id] = &observer;
        return id;
    }

    void unregister_observer(Id id) {
        observers.erase(id);
    }

private:
    Ref gen_ref() {
        return Ref(id_generator(), *this);
    }

    template <typename E>
    std::weak_ptr<E> add_entity(std::shared_ptr<E> entity) {
        Id id = entity->get_ref().get_id();
        entities[id] = entity;

        for (auto it = observers.begin(); it != observers.end(); ++it) {
            it->second->on_entity_added(std::static_pointer_cast<BaseEntity>(entity));
        }

        return entity;
    }

    std::unordered_map<Id, std::shared_ptr<BaseEntity>> entities;
    std::unordered_map<Id, EntityRepositoryObserver *> observers;
    Id (*id_generator)();
};

#endif
