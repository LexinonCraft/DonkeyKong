#ifndef FIXED_TIMESTEP_HPP
#define FIXED_TIMESTEP_HPP

#include <algorithm>

#include "DK/Constants.hpp"

/**
 * @brief A class that manages fixed timestep updates for a game loop.
 *
 * This class accumulates elapsed frame time and provides fixed-size update steps.
 * It ensures that the game logic is updated consistently, regardless of frame rate variations.
 */
class FixedTimestep {
public:
    /**
     * @brief Increases the accumulator by the elapsed frame time, clamped to a maximum value.
     * 
     * @param elapsed_time The time elapsed since the last frame, in seconds.
     */
    void add_frame_time(float elapsed_time) { accumulator += std::min(static_cast<double>(elapsed_time), constants::MAX_FRAME_TIME); }

    /**
     * @brief Checks if there is enough accumulated time to perform a fixed update step.
     * 
     * @return true if the accumulator has reached or exceeded the fixed timestep duration, false otherwise.
     */
    bool has_step() const { return accumulator >= constants::FIXED_DT; }

    /**
     * @brief Consumes a fixed update step from the accumulator.
     * 
     * @return The fixed timestep duration.
     */
    float consume_step() {
        accumulator -= constants::FIXED_DT;
        return static_cast<float>(constants::FIXED_DT);
    }

private:
    double accumulator = 0.0;
};

#endif
