#ifndef PLAYER_DEATH_ANIMATION_HPP
#define PLAYER_DEATH_ANIMATION_HPP

#include <memory>

#include "DK/model/animations/AbstractAnimation.hpp"
#include "DK/model/animations/AnimationVisitor.hpp"
#include "DK/model/entities/Player.hpp"

/**
 * @brief Animation that plays when the player dies.
 * 
 */
class PlayerDeathAnimation : public AbstractAnimation {
public:
    /** @brief States of the player death animation. */
    enum class State {
        NotStarted,      // Animation has not started yet.
        BeforeRotating,  // The player has not started rotating yet.
        Rotating,        // The player is rotating.
        AfterRotating,   // The player is lying on the ground after rotating.
        Finished,        // Animation has finished.
    };

    /**
     * @brief Initializes the player death animation.
     * 
     * @param stage The stage the animation is played on.
     * @param player The dying player.
     */
    PlayerDeathAnimation(Stage &stage, std::shared_ptr<Player> player) : AbstractAnimation(stage), player(player) {}

    void update(float dt) override;

    bool is_finished() override { return state == State::Finished; }

    void accept(AnimationVisitor &visitor) override { visitor.visit(*this); }

    /** @returns The current state of the animation. */
    State get_state() const { return state; }

    /** @returns The time elapsed in the current state. */
    float get_time_elapsed_in_state() const { return time_elapsed_in_state; }

    bool is_exit_animation() const override { return true; }

private:
    State state = State::NotStarted;
    std::shared_ptr<Player> player;
    float time_elapsed_in_state = 0.0f;

    /**
     * @brief Set a new state.
     * 
     * @param new_state The new state.
     * @param flag Flag to set to true.
     */
    void set_state(State new_state, bool &flag) {
        flag = true;
        state = new_state;
        time_elapsed_in_state = 0.0f;
    }
};

#endif
