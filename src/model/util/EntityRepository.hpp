#ifndef ENTITY_REPOSITORY_HPP
#define ENTITY_REPOSITORY_HPP

#include <memory>
#include <queue>
#include <unordered_map>

#include <SFML/System/Vector2.hpp>

#include "DK/model/Declarations.hpp"
#include "DK/model/entities/Girder.hpp"
#include "DK/model/entities/Ladder.hpp"
#include "DK/model/util/BaseEntity.hpp"
#include "DK/model/util/EntityRepositoryObserver.hpp"
#include "DK/model/util/Ref.hpp"
#include "DK/util/ObserverRegistry.hpp"

/**
 * @brief Repository storing all entities and forwarding entity lifecycle events.
 *
 * The repository is the central registry for the stage and notifies component
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
     * @brief Adds a barrel entity.
     * @param position Starting position of the barrel.
     * @returns Shared pointer to the created barrel entity.
     */
    std::shared_ptr<Barrel> add_barrel(sf::Vector2f position);

    /**
     * @brief Adds a hammer power-up entity.
     *
     * @param position Position of the hammer power-up.
     * @return Shared pointer to the created hammer power-up entity.
     */
    std::shared_ptr<HammerPowerUp> add_hammer_power_up(sf::Vector2f position);

    /**
     * @brief Adds a girder entity with red color.
     * @param left Left endpoint of the girder.
     * @param right Right endpoint of the girder.
     * @returns Shared pointer to the created girder entity.
     */
    std::shared_ptr<Girder> add_girder(sf::Vector2f left, sf::Vector2f right);

    /**
     * @brief Adds a girder entity with a specific color.
     * @param left Left endpoint of the girder.
     * @param right Right endpoint of the girder.
     * @param color Color of the girder.
     * @returns Shared pointer to the created girder entity.
     */
    std::shared_ptr<Girder> add_girder(sf::Vector2f left, sf::Vector2f right, Girder::Color color);

    /**
     * @brief Adds the player entity.
     * @returns Shared pointer to the created player entity.
     */
    std::shared_ptr<Player> add_player();

    /**
     * @brief Adds a ladder connecting two platform endpoints at an x-position with cyan color.
     * @param lower_end Lower platform endpoint.
     * @param upper_end Upper platform endpoint.
     * @param x_position Horizontal x-position of the ladder.
     * @param broken Whether the ladder is broken or not.
     * @returns Shared pointer to the created ladder entity.
     */
    std::shared_ptr<Ladder> add_ladder(std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_position,
                                       bool broken);

    /**
     * @brief Adds a ladder connecting two platform endpoints at an x-position with a specific color.
     * @param lower_end Lower platform endpoint.
     * @param upper_end Upper platform endpoint.
     * @param x_position Horizontal x-position of the ladder.
     * @param broken Whether the ladder is broken or not.
     * @param color Color of the ladder.
     * @returns Shared pointer to the created ladder entity.
     */
    std::shared_ptr<Ladder> add_ladder(std::shared_ptr<Platform> lower_end, std::shared_ptr<Platform> upper_end, float x_position,
                                       bool broken, Ladder::Color color);

    /**
     * @brief Adds a ladder connecting two y-positions at an x-position with a specific color.
     * @param lower_y Lower y-position of the ladder.
     * @param upper_y Upper y-position of the ladder.
     * @param x_pos Horizontal x-position of the ladder.
     * @param broken Whether the ladder is broken or not.
     * @param color Color of the ladder.
     * @param active_for_player Whether the ladder is active for the player.
     * @returns Shared pointer to the created ladder entity.
     */
    std::shared_ptr<Ladder> add_ladder(float lower_y, float upper_y, float x_pos, bool broken, Ladder::Color color, bool active_for_player);

    /**
     * @brief Adds a Donkey Kong entity.
     *
     * @param platform The platform on which Donkey Kong is placed.
     * @param x_position The horizontal position of Donkey Kong on the platform.
     * @param throw_barrels Whether Donkey Kong should throw barrels.
     * @return Shared pointer to the created Donkey Kong entity.
     */
    std::shared_ptr<DonkeyKong> add_donkey_kong(std::shared_ptr<Platform> platform, float x_position, bool throw_barrels);

    /**
     * @brief Adds a barrel stack entity.
     *
     * @param platform The platform on which the barrel stack is placed.
     * @param x_position The horizontal position of the barrel stack on the platform.
     * @return Shared pointer to the created barrel stack entity.
     */
    std::shared_ptr<BarrelStack> add_barrel_stack(std::shared_ptr<Platform> platform, float x_position);

    /**
     * @brief Adds a Pauline entity.
     *
     * @param platform The platform on which Pauline is placed.
     * @param x_position The horizontal position of Pauline on the platform.
     * @return Shared pointer to the created Pauline entity.
     */
    std::shared_ptr<Pauline> add_pauline(std::shared_ptr<Platform> platform, float x_position);

    /**
     * @brief Adds a dissolving platform entity.
     *
     * @param position The position of the dissolving platform.
     * @param width The width of the dissolving platform.
     * @return Shared pointer to the created dissolving platform entity.
     */
    std::shared_ptr<DissolvingPlatform> add_dissolving_platform(sf::Vector2f position, float width);

    /**
     * @brief Adds a ghost entity.
     *
     * @param platform The platform on which the ghost is placed.
     * @param x_pos The horizontal position of the ghost on the platform.
     * @return Shared pointer to the created ghost entity.
     */
    std::shared_ptr<Ghost> add_ghost(std::shared_ptr<Platform> platform, float x_pos);

    /**
     * @brief Adds a beam entity.
     *
     * @param lower_platform The lower platform to which the beam is attached.
     * @param upper_platform The upper platform to which the beam is attached.
     * @param x_pos The x-position of the beam.
     * @return Shared pointer to the created beam entity.
     */
    std::shared_ptr<Beam> add_beam(std::shared_ptr<Platform> lower_platform, std::shared_ptr<Platform> upper_platform, float x_pos);

    /**
     * @brief Schedules an entity for deletion in the next repository cleanup pass.
     * @param id Entity id to remove.
     */
    void prepare_for_deletion(Id id) { pending_deletions.push(id); }

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
     * @returns Iterator to the first entity.
     */
    auto begin() { return entities.begin(); }

    /**
     * @brief Returns an iterator to the end of the entity map.
     * @returns Iterator past the last entity.
     */
    auto end() { return entities.end(); }

    /** @returns The registry for repository event observers. */
    ObserverRegistry<EntityRepositoryObserver> &get_observer_registry() { return observer_registry; }

    /** @brief Clears all secondary entities (i.e. not Donkey Kong, Pauline or Jumpman) from the repository (and pending additions). */
    void clear_secondary_entities();

private:
    std::unordered_map<Id, std::shared_ptr<BaseEntity>> entities;
    ObserverRegistry<EntityRepositoryObserver> observer_registry;
    std::queue<std::shared_ptr<BaseEntity>> pending_additions;
    std::queue<Id> pending_deletions;
    Id (*id_generator)();

    /**
     * @brief Generates a reference for a new entity.
     * @returns Newly generated reference bound to this repository.
     */
    Ref gen_ref();

    /**
     * @brief Adds an entity to the repository and notifies observers.
     * @tparam E Concrete entity type.
     * @param entity Entity to insert.
     * @returns The inserted entity.
     */
    template <typename E> std::shared_ptr<E> add_entity(std::shared_ptr<E> entity) {
        pending_additions.push(std::static_pointer_cast<BaseEntity>(entity));
        return entity;
    }
};

#endif
