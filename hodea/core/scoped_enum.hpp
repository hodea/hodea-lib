// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Utilities to make use of scoped enums more convenient.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_SCOPED_ENUM_OR_OPERATOR_HPP_
#define _HODEA_SCOPED_ENUM_OR_OPERATOR_HPP_

#include <type_traits>

/**
 * Provide or operator in order to use scoped enums for bitmasks.
 */
#define DEFINE_SCOPED_ENUM_OR_OPERATOR(Enum) \
typedef std::underlying_type<Enum>::type Enum##_underlying_type;    \
                                                                    \
static inline constexpr Enum##_underlying_type operator |(          \
    Enum lhs, Enum rhs                                              \
    )                                                               \
{                                                                   \
    return                                                          \
        static_cast<Enum##_underlying_type>(lhs) |                  \
        static_cast<Enum##_underlying_type>(rhs);                   \
}

/**
 * Cast scoped enum to its underlying type.
 */
template <
    typename T,
    typename = typename std::enable_if<std::is_enum<T>::value>::type,
    typename T_underlying = typename std::underlying_type<T>::type 
    >
constexpr T_underlying to_underlying(T e) noexcept
{
    return static_cast<T_underlying>(e);
}

#endif /*!_HODEA_SCOPED_ENUM_OR_OPERATOR_HPP_ */
