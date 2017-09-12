// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Allow the use of scoped enums for bitmasks without casting.
 * 
 * This module allows to used scoped enums for bitmaks without the
 * need cast them to the underlaying type all the time.
 *
 * The idea for this was found on \see
 * http://blog.bitwigglers.org/using-enum-classes-as-type-safe-bitmasks
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_ENUM_BITMASK_HPP_
#define _HODEA_ENUM_BITMASK_HPP_

#include <type_traits>

namespace hodea {

#define ENABLE_ENUM_BITMASK(x)          \
namespace hodea {                       \
template<>                              \
struct Enable_enum_bitmask<x>           \
{                                       \
    static const bool enable = true;    \
};                                      \
}

template<typename T_enum>  
struct Enable_enum_bitmask  
{
    static const bool enable = false;
};

template<
    typename T_enum, 
    typename = typename std::enable_if<
        Enable_enum_bitmask<T_enum>::enable, T_enum >::type
    >
T_enum operator |(T_enum lhs, T_enum rhs)  
{
    using underlying = typename std::underlying_type<T_enum>::type;
    return static_cast<T_enum> (
        static_cast<underlying>(lhs) |
        static_cast<underlying>(rhs)
    );
}

template<
    typename T_enum, 
    typename T_underlying = typename std::underlying_type<T_enum>::type,
    typename = typename std::enable_if<
        Enable_enum_bitmask<T_enum>::enable, T_enum >::type
    >
constexpr T_underlying to_underlying(T_enum e)
{
    return static_cast<T_underlying>(e);
}

} // namespace hodea

#endif /*!_HODEA_ENUM_BITMASK_HPP_ */
