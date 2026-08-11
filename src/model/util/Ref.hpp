#ifndef REF_HPP
#define REF_HPP

#include "../Declarations.hpp"

class Ref {
public:
    Ref(Id id, EntityRepository &entity_repo) : id(id), entity_repo(entity_repo) {}

    Ref(const Ref &other) : id(other.id), entity_repo(other.entity_repo) {}

    Id get_id() const {
        return id;
    }
    
private:
    const Id id;
    EntityRepository &entity_repo;
};

#endif
