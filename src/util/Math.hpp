#ifndef MATH_HPP
#define MATH_HPP

/**
 * @brief Floor a float value to an integer.
 *
 * @param value The float value to be floored.
 * @return The floored integer value.
 */
int floor_to_int(float value);

/**
 * @brief Calculate the modulus of two integers, ensuring a non-negative result.
 *
 * @param a The first operand.
 * @param b The second operand (the divisor).
 * @return The modulus.
 */
int mod(int a, int b);

#endif
