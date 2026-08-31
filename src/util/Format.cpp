#include "DK/util/Format.hpp"

#include <iomanip>
#include <sstream>
#include <string>

std::string zero_pad_number(int value, int width) {
    std::ostringstream stream;
    stream << std::setw(width) << std::setfill('0') << value;
    return stream.str();
}
