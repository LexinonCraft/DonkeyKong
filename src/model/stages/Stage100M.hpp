#ifndef STAGE_100M_HPP
#define STAGE_100M_HPP

#include <list>
#include <memory>
#include <vector>

#include "DK/model/Stage.hpp"
#include "DK/model/util/EntityRepositoryObserver.hpp"

/**
 * @brief The 100m stage where the player must destroy the dissolving platforms.
 * 
 */
class Stage100M : public Stage, private EntityRepositoryObserver {
public:
    /**
     * @brief Initializes the 100m stage by creating the entities and setting the player's initial position.
     * 
     * @param rng A random number generator.
     * @param player_data The global player data.
     */
    Stage100M(int rng(), PlayerData &player_data);

    /** @brief When the stage is completed, this function clears the static entities and starts the completion animation. */
    void on_completed() override;

private:
    std::vector<std::shared_ptr<Girder>> spawn_suitable_girders;
    std::list<std::shared_ptr<DissolvingPlatform>> dissolving_platforms;
    std::vector<std::shared_ptr<Girder>> lower_falling_girders;
    std::shared_ptr<Girder> upper_falling_girder;
    std::vector<std::shared_ptr<BaseEntity>> static_entities_to_be_cleared;
    std::shared_ptr<DonkeyKong> donkey_kong;
    std::shared_ptr<Pauline> pauline;

    float time_since_last_spawn = 0.f;
    unsigned int ghost_count = 0;

    void update_while_running(float dt) override;

    /** @brief Spawn a ghost at a random position not too close to the player. */
    void spawn_ghost();

    /** @brief Checks if an entity is a ghost. */
    class IsGhostChecker : public EntityVisitor {
    public:
        bool is_ghost = false;

        virtual void visit(Barrel &barrel) override { is_ghost = false; }
        virtual void visit(Girder &girder) override { is_ghost = false; }
        virtual void visit(Player &player) override { is_ghost = false; }
        virtual void visit(Ladder &ladder) override { is_ghost = false; }
        virtual void visit(HammerPowerUp &hammer) override { is_ghost = false; }
        virtual void visit(DonkeyKong &donkey_kong) override { is_ghost = false; }
        virtual void visit(BarrelStack &barrel_stack) override { is_ghost = false; }
        virtual void visit(Pauline &pauline) override { is_ghost = false; }
        virtual void visit(DissolvingPlatform &dissolving_platform) override { is_ghost = false; }
        virtual void visit(Ghost &ghost) override { is_ghost = true; }
        virtual void visit(Beam &beam) override { is_ghost = false; }
    };

    void on_entity_added(std::shared_ptr<BaseEntity> entity) override {}

    /**
     * @brief Checks if the removed entity is a ghost, and if yes decrements the ghost count.
     * @param entity Entity that was removed.
     */
    void on_entity_removed(std::shared_ptr<BaseEntity> entity) override;
};

#endif
