#ifndef STAGE_25M_COMPLETION_ANIMATION_HPP
#define STAGE_25M_COMPLETION_ANIMATION_HPP

#include <memory>

#include "DK/model/Declarations.hpp"
#include "DK/model/animations/AbstractAnimation.hpp"
#include "DK/model/animations/AnimationVisitor.hpp"

/**
 * @brief Completion animation for the 25m stage.
 */
class Stage25MCompletionAnimation : public AbstractAnimation {
public:
    /** @brief The different states of the animation. */
    enum class State {
        NotStarted, // The animation has not started yet.
        United,     // Jumpman and Pauline are happily united.
        Climbing,   // Donkey Kong has grabbed Pauline again and is climbing up.
        Finished,   // The animation has finished.
    };

    /**
     * @brief Initializes the animation with the given stage, player, Donkey Kong, and Pauline.
     *
     * @param stage The stage where the animation takes place.
     * @param player The player.
     * @param donkey_kong Donkey Kong.
     * @param pauline Pauline.
     */
    Stage25MCompletionAnimation(Stage &stage, std::shared_ptr<Player> player, std::shared_ptr<DonkeyKong> donkey_kong,
                                std::shared_ptr<Pauline> pauline)
        : AbstractAnimation(stage), player(player), donkey_kong(donkey_kong), pauline(pauline) {}

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
    std::shared_ptr<DonkeyKong> donkey_kong;
    std::shared_ptr<Pauline> pauline;
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
