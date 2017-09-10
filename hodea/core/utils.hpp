// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Miscellaneous utilities which don't fit somewhere else.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_UTILS_HPP_
#define _HODEA_UTILS_HPP_

#include <cstddef>
#include <array>

namespace hodea {

/**
 * Deduce the number of entries in an array from its definition.
 *
 * This function returns the number of elements an array consists of,
 * provided that the compiler sees its definition and therefore know its
 * size at the point of time the function is used.
 *
 * \param[in] array
 *      The array for which to determine the number of entries it consists
 *      of.
 * \returns
 *      Number of entries the array consists of.

 * Example:
 *
 * \code
 * uint8_t buf[100];
 *
 * for (int i = 0; i < array_size(buf); i++)
 *     buf[i] = i;
 * \endcode
 */
template <typename T, std::size_t N >
constexpr std::size_t array_size(T (&)[N])
{
    return N;
}

} // namespace hodea

#endif /*!_HODEA_UTILS_HPP_ */
