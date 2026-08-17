#ifndef STAGE_25M_HPP
#define STAGE_25M_HPP

#include "../Stage.hpp"

class Stage25M : public Stage {
public:
    Stage25M(Id id_generator(), PlayerData &player_data);

private:
    float time_since_last_spawn = 0.f;
    std::shared_ptr<Girder> final_girder;

    void update_while_running(float dt) override;
};

#endif
