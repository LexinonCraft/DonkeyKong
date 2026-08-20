#ifndef STAGE_100M_HPP
#define STAGE_100M_HPP

#include <memory>
#include <vector>

#include "../Stage.hpp"

class Stage100M : public Stage {
public:
    Stage100M(Id id_generator(), PlayerData &player_data);

private:
    std::vector<std::shared_ptr<DissolvingPlatform>> dissolving_platforms;

    void update_while_running(float dt) override;
};

#endif
