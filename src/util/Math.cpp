#include <cmath>

#include "DK/util/Math.hpp"

int floor_to_int(float value) {
    return static_cast<int>(std::floor(value));
}

int mod(int a, int b) {
    int r = a % b;
    return r < 0 ? r + b : r;
}
