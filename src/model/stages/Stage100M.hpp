#ifndef STAGE_100M_HPP
#define STAGE_100M_HPP

#include "../Stage.hpp"

class Stage100M : public Stage {
public:
    Stage100M(Id id_generator(), PlayerData &player_data);

private:
    float time_since_last_spawn = 0.f;

    void update_while_running(float dt) override;
};

#endif
