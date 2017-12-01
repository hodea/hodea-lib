// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Math related functions.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_MATH_HPP_
#define _HODEA_MATH_HPP_

#include <type_traits>
#include <algorithm>

namespace hodea {

/**
 * Get minimum of two numbers.
 *
 * \param[in] a The first number.
 * \param[in] b The second number.
 *
 * \returns
 *      The smaller value of the two numbers.
 */
template <
    typename T,
    typename = typename std::enable_if<std::is_pod<T>::value>::type
    >
constexpr T math_min(T a, T b)
{
    return std::min(a, b);
}

/**
 * Get maximum of two numbers.
 *
 * \param[in] a The first number.
 * \param[in] b The second number.
 *
 * \returns
 *      The larger value of the two numbers.
 */
template <
    typename T,
    typename = typename std::enable_if<std::is_pod<T>::value>::type
    >
constexpr T math_max(T a, T b)
{
    return std::max(a, b);
}

/**
 * Limit value to a given range.
 *
 * \param[in] x   The value to limit.
 * \param[in] min The lower limit for the value.
 * \param[in] max The upper limit for the value.
 *
 * \returns
 *      Value limited to the given range.
 */
template <
    typename T,
    typename = typename std::enable_if<std::is_pod<T>::value>::type
    >
constexpr T math_limit(T x, T min, T max)
{
    return std::min(std::max(x, min), max);
}

/**
 * Limit value to a positive range.
 *
 * \param[in] x   The value to limit.
 *
 * \returns
 *      Value limited to a positive range.
 */
template <
    typename T,
    typename = typename std::enable_if<std::is_pod<T>::value>::type
    >
constexpr T math_limit_positive(T x)
{
    return std::max(0, x);
}

/**
 * Round floating point value to integer type, preferably at compile time.
 *
 * The function provides halfway rounding away from zero. The final
 * result is converted to the integer type specified as template parameter.
 *
 * If called with a floating point literal, the rounding and type
 * conversion is performed at compile time.
 *
 * \param[in] x The floating point value to round to the given type.
 *
 * \returns Rounded value converted to the desired type.
 *
 * Example
 *
 * @code
 * int foo = math_round_to<int>(1.75);
 * @endcode
 *
 * Will evaluate to
 *
 * @code
 * int foo = 2;
 * @endcode
 *
 * at compile time.
 */
template <
    typename T,
    typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
constexpr T math_round_to(double x)
{
    return static_cast<T>((x < 0) ? (x - 0.5) : (x + 0.5));
}

} // namespace hodea

#endif /*!_HODEA_MATH_HPP_ */
