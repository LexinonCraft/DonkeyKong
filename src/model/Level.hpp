#ifndef LEVEL_H
#define LEVEL_H

#include <memory>

#include "repository/PlatformRepository.hpp"
#include "repository/LadderRepository.hpp"
#include "repository/EntityRepository.hpp"
#include "../util/Declarations.hpp"

/// An abstract level
class Level {
public:
    virtual ~Level() {}

    PlatformRepository &get_platforms();
    LadderRepository &get_ladders();
    EntityRepository &get_entities();

    std::shared_ptr<Player> get_player() const;
    virtual void set_player(std::shared_ptr<Player> player); // TODO

    virtual void update(float dt);

protected:
    Level(RepositoryElementId id_generator());

    PlatformRepository platforms;
    LadderRepository ladders;
    EntityRepository entities;

    std::shared_ptr<Player> player;
};

#endif
