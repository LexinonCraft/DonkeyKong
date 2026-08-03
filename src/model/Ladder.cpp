#include "Ladder.hpp"

Ladder::Ladder(const Girder* lower_end, const Girder* upper_end, float x_pos)
    : lower_end(lower_end), upper_end(upper_end), x_pos(x_pos) {}

const Girder* Ladder::get_lower_end() const {
    return lower_end;
}
const Girder* Ladder::get_upper_end() const {
    return upper_end;
}
float Ladder::get_x_pos() const {
    return x_pos;
}
