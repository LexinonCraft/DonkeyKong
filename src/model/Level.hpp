#ifndef LEVEL_H
#define LEVEL_H

#include "util/EntityRepository.hpp"
#include "components/UpdatableComponentRepository.hpp"
#include "components/PlatformComponentRepository.hpp"
#include "Declarations.hpp"

/// An abstract level
class Level {
public:
    virtual ~Level() {}

    // std::shared_ptr<Player> get_player() const;
    // virtual void set_player(std::shared_ptr<Player> player); // TODO

    virtual void update(float dt);

    EntityRepository &get_entities() { return entities; }
    PlatformComponentRepository &get_platforms() { return platform_components; }

protected:
    Level(Id id_generator());

    EntityRepository entities;
    UpdatableComponentRepository updatable_components;
    PlatformComponentRepository platform_components;

    // std::shared_ptr<Player> player;
};

#endif
