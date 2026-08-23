#ifndef STAGE_HPP
#define STAGE_HPP

#include <memory>

#include "DK/Constants.hpp"
#include "DK/model/Declarations.hpp"
#include "DK/model/StageObserver.hpp"
#include "DK/model/animations/AbstractAnimation.hpp"
#include "DK/model/components/ClimbableComponentRepository.hpp"
#include "DK/model/components/EnemyComponentRepository.hpp"
#include "DK/model/components/JumpableComponentRepository.hpp"
#include "DK/model/components/PickableComponentRepository.hpp"
#include "DK/model/components/PlatformComponentRepository.hpp"
#include "DK/model/components/UpdatableComponentRepository.hpp"
#include "DK/model/util/EntityRepository.hpp"
#include "DK/util/ObserverRegistry.hpp"

/**
 * @brief Abstract game stage that owns the entity and component repositories.
 *
 * Concrete stages populate the entity repository with the stage's entities and define conditions for completing the stage.
 */
class Stage {
public:
    virtual ~Stage() {}

    /**
     * @brief Advances the stage state by one simulation step.
     * @param dt Time step in seconds.
     */
    void update(float dt);

    /** @returns The entity repository for this stage. */
    EntityRepository &get_entities() { return entities; }

    /** @returns The platform repository for this stage. */
    PlatformComponentRepository &get_platforms() { return platform_components; }

    /** @returns The climbable repository for this stage. */
    ClimbableComponentRepository &get_climbables() { return climbable_components; }

    /** @returns The enemy repository for this stage. */
    EnemyComponentRepository &get_enemies() { return enemy_components; }

    /** @returns The pickable repository for this stage. */
    PickableComponentRepository &get_pickables() { return pickable_components; }

    /** @returns The jumpable repository for this stage. */
    JumpableComponentRepository &get_jumpables() { return jumpable_components; }

    /** @returns The player entity associated with this stage. */
    std::shared_ptr<Player> get_player() const { return player; }

    /** @returns The global player data. */
    PlayerData &get_player_data() { return player_data; }

    /** @returns The x position of the left boundary of the stage, if any. */
    virtual std::optional<float> get_left_boundary() const { return 0.f; }

    /** @returns The x position of the right boundary of the stage, if any. */
    virtual std::optional<float> get_right_boundary() const { return static_cast<float>(constants::VIEW_WIDTH); }

    /** @returns Whether barrels can roll through the boundary at the given position. */
    virtual bool is_barrel_boundary_gap(const sf::Vector2f &position) const { return false; }

    /**
     * @brief Initializes the player death animation and notifies observers that the player has died. Called by the player entity when it
     * dies.
     */
    virtual void on_player_dying();

    /**
     * @brief Signals to the stage control when to switch to another scene (either the stage transition scene or the game over scene,
     * depending on the remaining amount of lives).
     *
     * @return true if the stage is over and the game should switch to another scene
     * @return false otherwise
     */
    bool is_over() { return ran_on_exit; }

    /**
     * @brief Adds the specified amount of score and notifies observers.
     *
     * @param position The position where the score was earned (relevant for the score effect animation).
     * @param score_to_add The amount of score to add.
     */
    void add_to_score(sf::Vector2f position, int score_to_add);

    /** @returns Whether the stage is currently running (i.e. no animation playing that pauses the game logic). */
    bool is_running() const { return !current_animation; }

    /** @returns A random integer using the stage's RNG. */
    int random_int() { return rng(); }

    /** @returns A registry with observers for different stage events. */
    ObserverRegistry<StageObserver> &get_observer_registry() { return observer_registry; }

    /** @returns The speed at which barrels roll in this level. */
    float get_barrel_roll_speed() const;

    /** @returns The multiplier for barrel speed based on the current level. */
    float get_barrel_difficulty_multiplier() const;

protected:
    /**
     * @brief Creates a stage and registers the component repositories with the entity repository.
     * @param rng Function used to generate random numbers.
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

    const std::shared_ptr<Player> player;
    PlayerData &player_data;
    float time_elapsed = 0.f;
    std::unique_ptr<AbstractAnimation> current_animation;
    bool player_died = false;
    bool ran_on_exit = false;

    /**
     * @brief Perform updates to be done while the game is running (i.e. no animation is playing that pauses the game logic).
     * @param dt Time step in seconds.
     */
    virtual void update_while_running(float dt);

    /** @brief Clears all secondary entities (i.e. not player, Donkey Kong and Pauline) from the stage. */
    void clear_secondary_entities() { entities.clear_secondary_entities(); }

    /** @brief Called when the stage is exited. Either advances the player to the next stage or takes a life from the player. */
    virtual void on_exit();

    /**
     * @brief Initializes the stage completion animation. Called by the stage itself when the player has met the conditions for completing
     * the stage.
     */
    virtual void on_completed() = 0;
};

#endif
