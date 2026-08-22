#ifndef STAGE_HPP
#define STAGE_HPP

#include <memory>

#include "../Constants.hpp"
#include "animations/AbstractAnimation.hpp"
#include "util/EntityRepository.hpp"
#include "components/UpdatableComponentRepository.hpp"
#include "components/PlatformComponentRepository.hpp"
#include "components/ClimbableComponentRepository.hpp"
#include "components/EnemyComponentRepository.hpp"
#include "components/JumpableComponentRepository.hpp"
#include "components/PickableComponentRepository.hpp"
#include "Declarations.hpp"
#include "../Constants.hpp"
#include "../util/ObserverRegistry.hpp"
#include "StageObserver.hpp"

/**
 * @brief Abstract game level that owns the entity and behaviour repositories.
 *
 * Concrete levels populate the repository with the world objects and expose the
 * player plus per-entity behaviour collections needed by the game loop.
 */
class Stage {
public:
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

    PickableComponentRepository &get_pickables() { return pickable_components; }

    /**
     * @brief Returns the jumpable repository for this level.
     * @return Repository containing jumpable behaviour components.
     */
    JumpableComponentRepository &get_jumpables() { return jumpable_components; }

    /**
     * @brief Returns the player associated with this level.
     * @return Shared pointer to the player entity.
     */
    std::shared_ptr<Player> get_player() const { return player; }

    PlayerData &get_player_data() { return player_data; }

    virtual std::optional<float> get_left_boundary() const { return 0.f; }

    virtual std::optional<float> get_right_boundary() const { return static_cast<float>(constants::VIEW_WIDTH); }

    virtual bool is_barrel_boundary_gap(const sf::Vector2f &position) const { return false; }

    virtual void on_player_dying();

    virtual void on_completed();

    bool is_over();

    void add_to_score(sf::Vector2f position, int score_to_add);

    bool is_running() const { return !current_animation; }

    int random_int() {
        return rng();
    }

    ObserverRegistry<StageObserver> &get_observer_registry() { return observer_registry; }
    float get_barrel_roll_speed() const;

    float get_barrel_difficulty_multiplier() const;

protected:
    /**
     * @brief Creates a level and registers the behaviour repositories with the entity repository.
     * @param id_generator Function used to generate fresh entity ids.
     */
    Stage(int rng(), PlayerData &player_data);

    int (*rng)();

    EntityRepository entities;
    UpdatableComponentRepository updatable_components;
    PlatformComponentRepository platform_components;
    ClimbableComponentRepository climbable_components;
    EnemyComponentRepository enemy_components;
    JumpableComponentRepository jumpable_components;
    PickableComponentRepository pickable_components;

    ObserverRegistry<StageObserver> observer_registry;
    float time_elapsed = 0.f;

    const std::shared_ptr<Player> player;
    PlayerData &player_data;
    bool player_died = false;
    bool ran_on_exit = false;

    std::unique_ptr<AbstractAnimation> current_animation;

    virtual void update_while_running(float dt);

    virtual void on_exit();
};

#endif
