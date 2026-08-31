#ifndef FIXED_TIMESTEP_HPP
#define FIXED_TIMESTEP_HPP

#include <algorithm>

#include "DK/Constants.hpp"

class FixedTimestep {
public:
    void add_frame_time(float elapsed_time) { accumulator += std::min(static_cast<double>(elapsed_time), constants::MAX_FRAME_TIME); }

    bool has_step() const { return accumulator >= constants::FIXED_DT; }

    float consume_step() {
        accumulator -= constants::FIXED_DT;
        return static_cast<float>(constants::FIXED_DT);
    }

private:
    double accumulator = 0.0;
};

#endif
