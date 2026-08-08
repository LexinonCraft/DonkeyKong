#ifndef PLATFORM_REPOSITORY_H
#define PLATFORM_REPOSITORY_H

#include "../Platform.hpp"
#include "../Girder.hpp"
#include "../../util/Repository.hpp"
#include "../../util/Declarations.hpp"

class PlatformRepository : public Repository<Platform> {
public:
    PlatformRepository(RepositoryElementId id_generator()) : Repository<Platform>(id_generator) {}

    Ref<Platform> add_girder(sf::Vector2f left, sf::Vector2f right) {
        Ref<Platform> ref = gen_ref();
        add(ref, std::make_shared<Girder>(ref, left, right));
        return ref;
    }
};

#endif