#ifndef STAGE_25M_HPP
#define STAGE_25M_HPP

#include <memory>

#include "DK/model/Stage.hpp"

/**
 * @brief The 25m stage where the player must climb to the top while avoiding barrels.
 */
class Stage25M : public Stage {
public:
    /**
     * @brief Initializes the stage by creating the entities and setting the player's starting position.
     *
     * @param rng A random number generator.
     * @param player_data The global player data.
     */
    Stage25M(int rng(), PlayerData &player_data);

    bool is_barrel_boundary_gap(const sf::Vector2f &position) const override;

    /**
     * @brief When the stage is completed, player the animation where Pauline and Jumpman are united at first but Donkey Kong then grabs
     * Pauline again and climbs up.
     */
    void on_completed() override;

private:
    float barrel_exit_y;
    std::shared_ptr<Girder> final_girder;
    std::shared_ptr<DonkeyKong> donkey_kong;
    std::shared_ptr<Pauline> pauline;

    void update_while_running(float dt) override;
};

#endif
