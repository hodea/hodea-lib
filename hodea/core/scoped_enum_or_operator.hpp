// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Macro to define binary OR operator for scoped enum.
 *
 * This file provides a macro which help to define the binary OR
 * operator for a scoped enum in order to construct bitmaks from it.
 * 
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_SCOPED_ENUM_OR_OPERATOR_HPP_
#define _HODEA_SCOPED_ENUM_OR_OPERATOR_HPP_

#include <type_traits>

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

#endif /*!_HODEA_SCOPED_ENUM_OR_OPERATOR_HPP_ */
