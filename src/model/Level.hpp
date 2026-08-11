#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "util/EntityRepository.hpp"
#include "components/UpdatableComponentRepository.hpp"
#include "components/PlatformComponentRepository.hpp"
#include "components/ClimbableComponentRepository.hpp"
#include "Declarations.hpp"
#include <memory>

/// An abstract level
class Level {
public:
    virtual ~Level() {}

    virtual void update(float dt);

    EntityRepository &get_entities() { return entities; }
    PlatformComponentRepository &get_platforms() { return platform_components; }
    ClimbableComponentRepository &get_climbables() { return climbable_components; }

    std::shared_ptr<Player> get_player() const { return player; }

protected:
    Level(Id id_generator());

    EntityRepository entities;
    UpdatableComponentRepository updatable_components;
    PlatformComponentRepository platform_components;
    ClimbableComponentRepository climbable_components;

    const std::shared_ptr<Player> player;
};

#endif
