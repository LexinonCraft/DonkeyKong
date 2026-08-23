#ifndef BASE_ENTITY_HPP
#define BASE_ENTITY_HPP

#include <memory>

#include "DK/model/Declarations.hpp"
#include "DK/model/util/Component.hpp"
#include "DK/model/util/EntityVisitor.hpp"
#include "DK/model/util/Ref.hpp"

/**
 * @brief Base class for all game entities in the hybrid ECS model.
 *
 * Each entity owns a stable repository reference and lifecycle state.
 */
class BaseEntity : public std::enable_shared_from_this<BaseEntity> {
public:
    /**
     * @brief Creates an entity bound to a repository reference.
     * @param ref Stable reference identifying the entity in its repository.
     */
    BaseEntity(Ref ref) : ref(ref) {}

    virtual ~BaseEntity() {}

    /**
     * @brief Returns the repository reference that identifies this entity.
     * @return The entity's reference object.
     */
    Ref get_ref() const { return ref; }

    /**
     * @brief Returns the unique id of this entity.
     * @return Entity id.
     */
    Id get_id() const { return ref.get_id(); }

    /**
     * @brief Returns whether the entity has been marked as destroyed.
     * @return True if the entity is pending destruction.
     */
    bool is_destroyed() const { return destroyed; }

    /**
     * @brief Clears a shared pointer when the pointed-to entity is already destroyed.
     * @tparam E Entity type stored in the shared_ptr.
     * @param entity Pointer to a possibly destroyed entity.
     * @return true if the pointer was reset because the entity was destroyed.
     * @return false otherwise
     */
    template <typename E> static bool handle_destroyed(std::shared_ptr<E> &entity) {
        if (entity && entity->is_destroyed()) {
            entity.reset();
            return true;
        }
        return false;
    }

    /**
     * @brief Clears a component-side pointer when the underlying entity has been destroyed.
     * @tparam T Type stored in the shared_ptr.
     * @param part_entity Pointer to an entity adapter or dependency.
     * @return true if the pointer was reset because the entity was destroyed.
     * @return false otherwise
     */
    template <typename T> static bool handle_destroyed_indirect(std::shared_ptr<T> &part_entity) {
        if (part_entity && part_entity->get_entity().is_destroyed()) {
            part_entity.reset();
            return true;
        }
        return false;
    }

    /** @brief Throws an exception if the entity has already been destroyed. */
    void assert_alive() const;

    /** @brief Validates and clears references to other entities that may have been deleted. Called every frame before updating. */
    virtual void check_referenced_entities() {}

    /**
     * @brief Accepts a visitor for type-based dispatch.
     * @param visitor Visitor instance to dispatch to.
     */
    virtual void accept(EntityVisitor &visitor) = 0;

    /**
     * @brief Creates the climbable component for this entity if supported.
     * @return Unique pointer to a climbable component or nullptr.
     */
    virtual std::unique_ptr<Component<Climbable>> create_climbable_component() { return nullptr; }

    /**
     * @brief Creates the platform component for this entity if supported.
     * @return Unique pointer to a platform component or nullptr.
     */
    virtual std::unique_ptr<Component<Platform>> create_platform_component() { return nullptr; }

    /**
     * @brief Creates the updatable component for this entity if supported.
     * @return Unique pointer to an updatable component or nullptr.
     */
    virtual std::unique_ptr<Component<Updatable>> create_updatable_component() { return nullptr; }

    /**
     * @brief Creates the enemy component for this entity if supported.
     * @return Unique pointer to an enemy component or nullptr.
     */
    virtual std::unique_ptr<Component<Enemy>> create_enemy_component() { return nullptr; }

    /**
     * @brief Creates the jumpable component for this entity if supported.
     * @return Unique pointer to a jumpable component or nullptr.
     */
    virtual std::unique_ptr<Component<Jumpable>> create_jumpable_component() { return nullptr; }

    /**
     * @brief Creates the pickable component for this entity if supported.
     * @return Unique pointer to a pickable component or nullptr.
     */
    virtual std::unique_ptr<Component<Pickable>> create_pickable_component() { return nullptr; }

    /** @returns Whether the entity is secondary (i.e. not the player, Donkey Kong or Pauline). */
    virtual bool is_secondary_entity() const { return true; }

    /** @brief Marks the entity for deletion by the repository. */
    void destroy();

private:
    Ref ref;
    bool destroyed = false;
};

#endif
