// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Helper to constrain template parameters to certain types.
 *
 * \author f.hollerer@hodea.org
 */
#if !defined HODEA_TYPE_CONSTRAINTS_HPP
#define HODEA_TYPE_CONSTRAINTS_HPP

#include <type_traits>

namespace hodea {

/**
 * Helper template to check if type is an integral type.
 */
template <
    typename T,
    typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
struct enable_if_integral_type
{
    typedef T type;
};

/**
 * Helper template to check if type is an unsigned type.
 */
template <
    typename T,
    typename = typename std::enable_if<std::is_unsigned<T>::value>::type
    >
struct enable_if_unsigned_type
{
    typedef T type;
};

/**
 * Helper template to check if type can represent a bitmask.
 */
template <
    typename T,
    typename = typename std::enable_if<
        std::is_integral<T>::value || std::is_enum<T>::value>::type
    >
struct enable_if_bitmask_type
{
    typedef T type;
};

} // namespace hodea

#endif /*!HODEA_TYPE_CONSTRAINTS_HPP */
