#ifndef ENTITY_REPOSITORY_HPP
#define ENTITY_REPOSITORY_HPP

#include <SFML/System/Vector2.hpp>
#include <memory>
#include <queue>
#include <unordered_map>

#include "../Declarations.hpp"
#include "EntityRepositoryObserver.hpp"
#include "BaseEntity.hpp"
#include "../entities/Barrel.hpp"
#include "../entities/Girder.hpp"
#include "../entities/Player.hpp"
#include "../entities/Ladder.hpp"
#include "../entities/DonkeyKong.hpp"
#include "../entities/BarrelStack.hpp"
#include "Ref.hpp"

/**
 * @brief Repository storing all entities and forwarding entity lifecycle events.
 *
 * The repository is the central registry for the level and notifies component
 * repositories whenever an entity is added or removed.
 */
class EntityRepository {
public:
    /**
     * @brief Creates a repository bound to an id-generating function.
     * @param id_generator Callback used to allocate fresh entity ids.
     */
    EntityRepository(Id (*id_generator)()) : id_generator(id_generator) {}

    /**
     * @brief Adds a barrel entity at the given coordinates.
     * @param position Starting position of the barrel.
     * @return Shared pointer to the created barrel.
     */
    std::shared_ptr<Barrel> add_barrel(sf::Vector2f position) {
        return add_entity(std::make_shared<Barrel>(gen_ref(), position));
    }

    /**
     * @brief Adds a girder entity spanning the two endpoints.
     * @param left Left endpoint of the girder.
     * @param right Right endpoint of the girder.
     * @return Shared pointer to the created girder.
     */
    std::shared_ptr<Girder> add_girder(sf::Vector2f left, sf::Vector2f right) {
        return add_entity(std::make_shared<Girder>(gen_ref(), left, right));
    }

    /**
     * @brief Adds a girder entity spanning the two endpoints.
     * @param left Left endpoint of the girder.
     * @param right Right endpoint of the girder.
     * @return Shared pointer to the created girder.
     */
    std::shared_ptr<Girder> add_girder(sf::Vector2f left, sf::Vector2f right, Girder::Color color) {
        return add_entity(std::make_shared<Girder>(gen_ref(), left, right, color));
    }

    /**
     * @brief Adds the player entity.
     * @return Shared pointer to the created player.
     */
    std::shared_ptr<Player> add_player() {
        return add_entity(std::make_shared<Player>(gen_ref()));
    }

    /**
     * @brief Adds a ladder connecting two platform endpoints at an x-position.
     * @param lower_end Lower platform endpoint.
     * @param upper_end Upper platform endpoint.
     * @param x_position Horizontal x-position of the ladder.
     * @return Shared pointer to the created ladder.
     */
    std::shared_ptr<Ladder> add_ladder(std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_position, bool broken) {
        return add_entity(std::make_shared<Ladder>(gen_ref(), lower_end, upper_end, x_position, broken));
    }

    /**
     * @brief Adds a ladder connecting two platform endpoints at an x-position.
     * @param lower_end Lower platform endpoint.
     * @param upper_end Upper platform endpoint.
     * @param x_position Horizontal x-position of the ladder.
     * @param color Color of the ladder.
     * @return Shared pointer to the created ladder.
     */
    std::shared_ptr<Ladder> add_ladder(std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_position, bool broken, Ladder::Color color) {
        return add_entity(std::make_shared<Ladder>(gen_ref(), lower_end, upper_end, x_position, broken, color));
    }

    std::shared_ptr<DonkeyKong> add_donkey_kong(std::shared_ptr<Platform> platform, float x_position, bool throw_barrels) {
        return add_entity(std::make_shared<DonkeyKong>(gen_ref(), platform, x_position, throw_barrels));
    }

    std::shared_ptr<BarrelStack> add_barrel_stack(std::shared_ptr<Platform> platform, float x_position) {
        return add_entity(std::make_shared<BarrelStack>(gen_ref(), platform, x_position));
    }

    /**
     * @brief Schedules an entity for deletion in the next repository cleanup pass.
     * @param id Entity id to remove.
     */
    void prepare_for_deletion(Id id) {
        pending_deletions.push(id);
    }

    /**
     * @brief Removes all entities queued for deletion and validates remaining references.
     */
    void handle_deletions();

    /**
     * @brief Returns an iterator to the beginning of the entity map.
     * @return Iterator to the first entity.
     */
    auto begin() {
        return entities.begin();
    }

    /**
     * @brief Returns an iterator to the end of the entity map.
     * @return Iterator past the last entity.
     */
    auto end() {
        return entities.end();
    }

    /**
     * @brief Registers an observer for repository events.
     * @param observer Observer to notify when entities are added or removed.
     * @return Observer id used to unregister this observer later.
     */
    Id register_observer(EntityRepositoryObserver &observer) {
        Id id = id_generator();
        observers[id] = &observer;
        return id;
    }

    /**
     * @brief Unregisters an observer from future repository events.
     * @param id Observer id returned by register_observer().
     */
    void unregister_observer(Id id) {
        observers.erase(id);
    }

private:
    /**
     * @brief Generates a reference for a new entity.
     * @return Newly generated reference bound to this repository.
     */
    Ref gen_ref() {
        return Ref(id_generator(), *this);
    }

    /**
     * @brief Adds an entity to the repository and notifies observers.
     * @tparam E Concrete entity type.
     * @param entity Entity to insert.
     * @return The inserted entity.
     */
    template <typename E>
    std::shared_ptr<E> add_entity(std::shared_ptr<E> entity) {
        Id id = entity->get_ref().get_id();
        entities[id] = entity;

        for (auto it = observers.begin(); it != observers.end(); ++it) {
            it->second->on_entity_added(std::static_pointer_cast<BaseEntity>(entity));
        }

        return entity;
    }

    std::unordered_map<Id, std::shared_ptr<BaseEntity>> entities;
    std::unordered_map<Id, EntityRepositoryObserver *> observers;
    std::queue<Id> pending_deletions;
    Id (*id_generator)();
};

#endif
