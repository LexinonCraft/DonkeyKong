#ifndef STAGE_100M_HPP
#define STAGE_100M_HPP

#include <memory>
#include <vector>
#include <list>

#include "DK/model/Stage.hpp"
#include "DK/model/animations/Stage100MCompletionAnimation.hpp"

class Stage100M : public Stage {
public:
    Stage100M(Id id_generator(), PlayerData &player_data);

    void on_completed() override {
        Stage::on_completed();
        
        clear_secondary_entities();
        for (auto it = static_entities_to_be_cleared.begin(); it != static_entities_to_be_cleared.end(); ++it) {
            it->get()->destroy();
        }

        current_animation = std::make_unique<Stage100MCompletionAnimation>(*this, lower_falling_girders, upper_falling_girder, player, donkey_kong, pauline);
    }

private:
    std::vector<std::shared_ptr<Girder>> spawn_suitable_girders;
    std::list<std::shared_ptr<DissolvingPlatform>> dissolving_platforms;
    std::vector<std::shared_ptr<Girder>> lower_falling_girders;
    std::shared_ptr<Girder> upper_falling_girder;
    std::vector<std::shared_ptr<BaseEntity>> static_entities_to_be_cleared;
    std::shared_ptr<DonkeyKong> donkey_kong;
    std::shared_ptr<Pauline> pauline;

    float time_since_last_spawn = 0.f;
    unsigned int ghost_count = 0; // TODO: decrement this count when a ghost is killed

    void update_while_running(float dt) override;

    void spawn_ghost();
};

#endif
