#ifndef PLATFORM_REPOSITORY_H
#define PLATFORM_REPOSITORY_H

#include <memory>

#include "../Platform.hpp"
#include "../Girder.hpp"
#include "../../util/Repository.hpp"
#include "../../util/Declarations.hpp"

class PlatformRepository : public Repository<Platform> {
public:
    PlatformRepository(RepositoryElementId id_generator()) : Repository<Platform>(id_generator) {}

    std::shared_ptr<Girder> add_girder(sf::Vector2f left, sf::Vector2f right) {
        Ref<Platform> ref = gen_ref();
        return add(ref, std::make_shared<Girder>(ref, left, right));
    }
};

#endif