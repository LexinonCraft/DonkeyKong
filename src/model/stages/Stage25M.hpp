#ifndef STAGE_25M_HPP
#define STAGE_25M_HPP

#include <memory>

#include "DK/model/Stage.hpp"
#include "DK/model/animations/Stage25MCompletionAnimation.hpp"

class Stage25M : public Stage {
public:
    Stage25M(Id id_generator(), PlayerData &player_data);

    bool is_barrel_boundary_gap(const sf::Vector2f &position) const override;

    void on_completed() override { current_animation = std::make_unique<Stage25MCompletionAnimation>(*this, player, donkey_kong, pauline); }

private:
    float barrel_exit_y;
    std::shared_ptr<Girder> final_girder;
    std::shared_ptr<DonkeyKong> donkey_kong;
    std::shared_ptr<Pauline> pauline;

    void update_while_running(float dt) override;
};

#endif
