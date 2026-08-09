#ifndef ENTITY_REPOSITORY_H
#define ENTITY_REPOSITORY_H

#include "../Entity.hpp"
#include "../Player.hpp"
#include "../Barrel.hpp"
#include "../../util/Repository.hpp"
#include "../../util/Declarations.hpp"

class EntityRepository : public Repository<Entity> {
public:
    EntityRepository(RepositoryElementId id_generator()) : Repository<Entity>(id_generator) {}

    std::shared_ptr<Player> add_player() {
        Ref<Entity> ref = gen_ref();
        return add(ref, std::make_shared<Player>(ref));
    }

    std::shared_ptr<Barrel> add_barrel(sf::Vector2f position) {
        Ref<Entity> ref = gen_ref();
        return add(ref, std::make_shared<Barrel>(ref, position));
    }
};
    
#endif