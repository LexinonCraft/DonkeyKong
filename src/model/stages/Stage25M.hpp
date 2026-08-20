#ifndef STAGE_25M_HPP
#define STAGE_25M_HPP

#include "../Stage.hpp"

class Stage25M : public Stage {
public:
    Stage25M(Id id_generator(), PlayerData &player_data);

    bool is_barrel_boundary_gap(const sf::Vector2f &position) const override;

private:
    float time_since_last_spawn = 0.f;
    float barrel_exit_y;
    std::shared_ptr<Girder> final_girder;

    void update_while_running(float dt) override;
};

#endif
