#ifndef STAGE_100M_COMPLETION_ANIMATION_HPP
#define STAGE_100M_COMPLETION_ANIMATION_HPP

#include <memory>
#include <vector>

#include "DK/model/Declarations.hpp"
#include "DK/model/animations/AbstractAnimation.hpp"
#include "DK/model/animations/AnimationVisitor.hpp"

/**
 * @brief Completion animation for the 100m stage.
 */
class Stage100MCompletionAnimation : public AbstractAnimation {
public:
    /** @brief The possible states of the animation. */
    enum class State {
        NotStarted, // The animation has not started yet.
        BeforeFall, // The girders have fallen, but Donkey Kong is still levitating.
        Falling,    // Donkey Kong is falling down.
        Impact,     // Donkey Kong has hit the ground.
        United,     // Donkey Kong and Pauline are united on the upper girder.
        Finished,   // The animation has finished.
    };

    /**
     * @brief Initializes the animation with the given stage, girders, player, Donkey Kong, and Pauline.
     *
     * @param stage The stage on which the animation takes place.
     * @param lower_falling_girders The girders that fall down onto the lowest platform.
     * @param upper_falling_girder The girder on which Jumpan and Pauline will be united.
     * @param player The player character (Jumpan).
     * @param donkey_kong Donkey Kong.
     * @param pauline Pauline.
     */
    Stage100MCompletionAnimation(Stage &stage, std::vector<std::shared_ptr<Girder>> lower_falling_girders,
                                 std::shared_ptr<Girder> upper_falling_girder, std::shared_ptr<Player> player,
                                 std::shared_ptr<DonkeyKong> donkey_kong, std::shared_ptr<Pauline> pauline)
        : AbstractAnimation(stage), lower_falling_girders(lower_falling_girders), upper_falling_girder(upper_falling_girder),
          player(player), donkey_kong(donkey_kong), pauline(pauline) {}

    void update(float dt) override;

    bool is_finished() override { return state == State::Finished; }

    void accept(AnimationVisitor &visitor) override { visitor.visit(*this); }

    /** @returns The current state of the animation. */
    State get_state() const { return state; }

    /** @returns The time elapsed in the current state. */
    float get_time_elapsed_in_state() const { return time_elapsed_in_state; }

    bool is_exit_animation() const override { return true; }

private:
    std::vector<std::shared_ptr<Girder>> lower_falling_girders;
    std::shared_ptr<Girder> upper_falling_girder;
    std::shared_ptr<Player> player;
    std::shared_ptr<DonkeyKong> donkey_kong;
    std::shared_ptr<Pauline> pauline;

    State state = State::NotStarted;
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
