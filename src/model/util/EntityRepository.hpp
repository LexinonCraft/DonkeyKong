#ifndef ENTITY_REPOSITORY_HPP
#define ENTITY_REPOSITORY_HPP

#include <SFML/System/Vector2.hpp>
#include <memory>
#include <queue>
#include <unordered_map>

#include "DK/model/Declarations.hpp"
#include "DK/model/util/EntityRepositoryObserver.hpp"
#include "DK/model/util/BaseEntity.hpp"
#include "DK/model/entities/Barrel.hpp"
#include "DK/model/entities/Girder.hpp"
#include "DK/model/entities/HammerPowerUp.hpp"
#include "DK/model/entities/Player.hpp"
#include "DK/model/entities/Ladder.hpp"
#include "DK/model/entities/DonkeyKong.hpp"
#include "DK/model/entities/BarrelStack.hpp"
#include "DK/model/entities/Pauline.hpp"
#include "DK/model/entities/DissolvingPlatform.hpp"
#include "DK/util/ObserverRegistry.hpp"
#include "DK/model/entities/Ghost.hpp"
#include "DK/model/entities/Beam.hpp"
#include "DK/model/util/Ref.hpp"

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
    EntityRepository(Id (*id_generator)()) : observer_registry(id_generator), id_generator(id_generator) {}

    /**
     * @brief Adds a barrel entity at the given coordinates.
     * @param position Starting position of the barrel.
     * @return Shared pointer to the created barrel.
     */
    std::shared_ptr<Barrel> add_barrel(sf::Vector2f position) {
        return add_entity(std::make_shared<Barrel>(gen_ref(), position));
    }

    std::shared_ptr<HammerPowerUp> add_hammer_power_up(sf::Vector2f position) {
        return add_entity(std::make_shared<HammerPowerUp>(gen_ref(), position));
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

    std::shared_ptr<Ladder> add_ladder(float lower_y, float upper_y, float x_pos, bool broken, Ladder::Color color, bool active_for_player) {
        return add_entity(std::make_shared<Ladder>(gen_ref(), lower_y, upper_y, x_pos, broken, color, active_for_player));
    }

    std::shared_ptr<DonkeyKong> add_donkey_kong(std::shared_ptr<Platform> platform, float x_position, bool throw_barrels) {
        return add_entity(std::make_shared<DonkeyKong>(gen_ref(), platform, x_position, throw_barrels));
    }

    std::shared_ptr<BarrelStack> add_barrel_stack(std::shared_ptr<Platform> platform, float x_position) {
        return add_entity(std::make_shared<BarrelStack>(gen_ref(), platform, x_position));
    }

    std::shared_ptr<Pauline> add_pauline(std::shared_ptr<Platform> platform, float x_position) {
        return add_entity(std::make_shared<Pauline>(gen_ref(), platform, x_position));
    }

    std::shared_ptr<DissolvingPlatform> add_dissolving_platform(sf::Vector2f position, float width) {
        return add_entity(std::make_shared<DissolvingPlatform>(gen_ref(), position, width));
    }

    std::shared_ptr<Ghost> add_ghost(std::shared_ptr<Platform> platform, float x_pos) {
        return add_entity(std::make_shared<Ghost>(gen_ref(), platform, x_pos));
    }
    
    std::shared_ptr<Beam> add_beam(std::shared_ptr<Platform> lower_platform, std::shared_ptr<Platform> upper_platform, float x_pos) {
        return add_entity(std::make_shared<Beam>(gen_ref(), lower_platform, upper_platform, x_pos));
    }

    /**
     * @brief Schedules an entity for deletion in the next repository cleanup pass.
     * @param id Entity id to remove.
     */
    void prepare_for_deletion(Id id) {
        pending_deletions.push(id);
    }

    /**
     * @brief Adds all entities queued for insertion and notifies observers.
     */
    void handle_additions();

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

    std::queue<std::shared_ptr<BaseEntity>>& get_pending_additions() {
        return pending_additions;
    }

    ObserverRegistry<EntityRepositoryObserver> &get_observer_registry() {
        return observer_registry;
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
        pending_additions.push(std::static_pointer_cast<BaseEntity>(entity));
        return entity;
    }

    std::unordered_map<Id, std::shared_ptr<BaseEntity>> entities;
    ObserverRegistry<EntityRepositoryObserver> observer_registry;
    std::queue<std::shared_ptr<BaseEntity>> pending_additions;
    std::queue<Id> pending_deletions;
    Id (*id_generator)();
};

#endif
