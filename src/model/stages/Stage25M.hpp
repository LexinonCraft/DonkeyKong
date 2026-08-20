#ifndef STAGE_25M_HPP
#define STAGE_25M_HPP

#include "../Stage.hpp"

class Stage25M : public Stage {
public:
    Stage25M(Id id_generator(), PlayerData &player_data);

private:
    std::shared_ptr<Girder> final_girder;
    std::shared_ptr<Pauline> pauline;
    std::shared_ptr<DonkeyKong> donkey_kong;

    void update_while_running(float dt) override;
};

#endif
