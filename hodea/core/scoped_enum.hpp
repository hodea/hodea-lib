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
 * Cast enum to its underlying type.
 */
template <
    typename T,
    typename = typename std::enable_if<std::is_enum<T>::value>::type,
    typename T_underlying = typename std::underlying_type<T>::type 
    >
constexpr T_underlying enum_to_underlying(T e) noexcept
{
    return static_cast<T_underlying>(e);
}

/**
 * Provide or operator in order to use scoped enums for bitmasks.
 */
#define DEFINE_SCOPED_ENUM_OR_OPERATOR(Enum) \
static inline constexpr Enum operator |(Enum lhs, Enum rhs)             \
{                                                                       \
    return static_cast<Enum>(                                           \
                enum_to_underlying(lhs) | enum_to_underlying(rhs)       \
                );                                                      \
}


#endif /*!_HODEA_SCOPED_ENUM_OR_OPERATOR_HPP_ */
