#ifndef REF_HPP
#define REF_HPP

#include "DK/model/Declarations.hpp"

/**
 * @brief Stable reference to an entity within a repository.
 *
 * A reference keeps the entity id and the owning repository together so that an
 * entity can safely schedule deletion or resolve repository-level operations.
 */
class Ref {
public:
    /**
     * @brief Creates a reference with a repository and entity id.
     * @param id Unique id of the referenced entity.
     * @param entity_repo Repository that owns the entity.
     */
    Ref(Id id, EntityRepository &entity_repo) : id(id), entity_repo(entity_repo) {}

    /**
     * @brief Copy constructor.
     * @param other Reference to copy.
     */
    Ref(const Ref &other) : id(other.id), entity_repo(other.entity_repo) {}

    /**
     * @brief Returns the entity id inside the reference.
     * @return Entity id.
     */
    Id get_id() const { return id; }

    /**
     * @brief Returns the repository associated with this reference.
     * @return Owning entity repository.
     */
    EntityRepository &get_repository() const { return entity_repo; }

private:
    const Id id;
    EntityRepository &entity_repo;
};

#endif
