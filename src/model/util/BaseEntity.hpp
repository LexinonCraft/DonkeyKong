#ifndef BASE_ENTITY_HPP
#define BASE_ENTITY_HPP

#include <stdexcept>
#include <memory>

#include "../Declarations.hpp"
#include "EntityVisitor.hpp"
#include "Ref.hpp"

class BaseEntity {
public:
    BaseEntity(Ref ref) : ref(ref) {}

    virtual ~BaseEntity() {}

    Ref get_ref() const {
        return ref;
    }

    Id get_id() const {
        return ref.get_id();
    }

    bool is_destroyed() const {
        return destroyed;
    }

    template <typename E>
    static bool handle_destroyed(std::shared_ptr<E> &entity) {
        if (entity && entity->is_destroyed()) {
            entity.reset();
            return true;
        }
        return false;
    }

    template <typename T>
    static bool handle_destroyed_indirect(std::shared_ptr<T> &part_entity) {
        if (part_entity && part_entity->get_entity().is_destroyed()) {
            part_entity.reset();
            return true;
        }
        return false;
    }

    void assert_alive() const;

    virtual void check_referenced_entities() {}

    virtual void accept(EntityVisitor &visitor) = 0;

protected:
    void destroy();

private:
    Ref ref;
    bool destroyed = false;
};

#endif
