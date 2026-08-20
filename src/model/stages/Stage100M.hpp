#ifndef STAGE_100M_HPP
#define STAGE_100M_HPP

#include <memory>
#include <vector>

#include "../Stage.hpp"

class Stage100M : public Stage {
public:
    Stage100M(Id id_generator(), PlayerData &player_data);

private:
    std::vector<std::shared_ptr<Girder>> spawn_suitable_girders;

    float time_since_last_spawn = 0.f;
    unsigned int ghost_count = 0; // TODO: decrement this count when a ghost is killed

    void update_while_running(float dt) override;

    void spawn_ghost();
};

#endif
