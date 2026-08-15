#ifndef STAGE_HPP
#define STAGE_HPP

#include <memory>

#include "util/EntityRepository.hpp"
#include "components/UpdatableComponentRepository.hpp"
#include "components/PlatformComponentRepository.hpp"
#include "components/ClimbableComponentRepository.hpp"
#include "components/EnemyComponentRepository.hpp"
#include "Declarations.hpp"
#include "Constants.hpp"

/**
 * @brief Abstract game level that owns the entity and behaviour repositories.
 *
 * Concrete levels populate the repository with the world objects and expose the
 * player plus per-entity behaviour collections needed by the game loop.
 */
class Stage {
public:
    enum class StageId {
        Stage25M,
        Stage50M,
        Stage75M,
        Stage100M,
    };

    enum class StageState {
        Running,
        PlayerDying,
        PlayerDead,
        Completed,
    };

    virtual ~Stage() {}

    /**
     * @brief Advances the level state by one simulation step.
     * @param dt Time step in seconds.
     */
    void update(float dt);

    /**
     * @brief Returns the entity repository for this level.
     * @return Repository containing all active entities.
     */
    EntityRepository &get_entities() { return entities; }

    /**
     * @brief Returns the platform repository for this level.
     * @return Repository containing platform behaviour components.
     */
    PlatformComponentRepository &get_platforms() { return platform_components; }

    /**
     * @brief Returns the climbable repository for this level.
     * @return Repository containing ladder and climbable components.
     */
    ClimbableComponentRepository &get_climbables() { return climbable_components; }

    /**
     * @brief Returns the enemy repository for this level.
     * @return Repository containing enemy behaviour components.
     */
    EnemyComponentRepository &get_enemies() { return enemy_components; }

    /**
     * @brief Returns the player associated with this level.
     * @return Shared pointer to the player entity.
     */
    std::shared_ptr<Player> get_player() const { return player; }

    PlayerData &get_player_data() { return player_data; }

    virtual std::optional<float> get_left_boundary() const { return 0.f; }

    virtual std::optional<float> get_right_boundary() const { return static_cast<float>(constants::VIEW_WIDTH); }

    virtual void on_player_dying();

    StageState get_state() const { return state; }

protected:
    /**
     * @brief Creates a level and registers the behaviour repositories with the entity repository.
     * @param id_generator Function used to generate fresh entity ids.
     */
    Stage(Id id_generator(), PlayerData &player_data);

    EntityRepository entities;
    UpdatableComponentRepository updatable_components;
    PlatformComponentRepository platform_components;
    ClimbableComponentRepository climbable_components;
    EnemyComponentRepository enemy_components;

    StageState state = StageState::Running;
    float time_elapsed = 0.f;
    float time_since_state_change = 0.f;

    const std::shared_ptr<Player> player;
    PlayerData &player_data;

    virtual void update_while_running(float dt);
};

#endif
