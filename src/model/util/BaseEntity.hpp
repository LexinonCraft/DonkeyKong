#ifndef BASE_ENTITY_HPP
#define BASE_ENTITY_HPP

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

    virtual void accept(EntityVisitor &visitor) = 0;

private:
    Ref ref;
};

#endif
