#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <string>

/**
 * @brief Converts an integer value to a string and pads it with leading zeros to achieve the specified width.
 *
 * @param value The integer value to be converted and padded.
 * @param width The desired width of the resulting string. If the number of digits in the value is less than this width, leading zeros will
 * be added.
 * @return The resulting string representation of the integer value, padded with leading zeros if necessary.
 */
std::string zero_pad_number(int value, int width);

#endif
