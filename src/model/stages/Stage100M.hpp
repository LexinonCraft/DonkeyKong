#ifndef STAGE_100M_HPP
#define STAGE_100M_HPP

#include <memory>
#include <vector>
#include <list>

#include "../Stage.hpp"
#include "../animations/Stage100MCompletionAnimation.hpp"

class Stage100M : public Stage {
public:
    Stage100M(Id id_generator(), PlayerData &player_data);

    void on_completed() override {
        Stage::on_completed();
        current_animation = std::make_unique<Stage100MCompletionAnimation>(*this);
    }

private:
    std::vector<std::shared_ptr<Girder>> spawn_suitable_girders;
    std::list<std::shared_ptr<DissolvingPlatform>> dissolving_platforms;

    float time_since_last_spawn = 0.f;
    unsigned int ghost_count = 0; // TODO: decrement this count when a ghost is killed

    void update_while_running(float dt) override;

    void spawn_ghost();
};

#endif
