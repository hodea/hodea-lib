// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Reverse byte order of unsigned types various sizes.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_USWAP_HPP_
#define _HODEA_USWAP_HPP_

#include <stdint.h>

namespace hodea {

/**
 * Reverse byte order of an unsigned 16 bit value.
 *
 * \param[in] x
 *      The unsigned 16 bit value to reverse the byte order.
 * \returns
 *      Unsigned 16 bit value with reversed byte order.
 */
static inline constexpr uint16_t uswap16(uint16_t x)
{
    return ((x & 0xff00U) >> 8) | ((x & 0x00ffU) << 8);
}

/**
 * Reverse byte order of an unsigned 32 bit value.
 *
 * \param[in] x
 *      The unsigned 32 bit value to reverse the byte order.
 * \returns
 *      Unsigned 32 bit value with reversed byte order.
 */
static inline constexpr uint32_t uswap32(uint32_t x)
{
    return ((x & 0xff000000U) >> 24) |
           ((x & 0x00ff0000U) >>  8) |
           ((x & 0x0000ff00U) <<  8) |
           ((x & 0x000000ffU) << 24);
}

/**
 * Reverse byte order of an unsigned 64 bit value.
 *
 * \param[in] x
 *      The unsigned 64 bit value to reverse the byte order.
 * \returns
 *      Unsigned 64 bit value with reversed byte order.
 */
static inline constexpr uint64_t uswap64(uint64_t x)
{
    return ((x & 0xff00000000000000ULL) >> 56) |
           ((x & 0x00ff000000000000ULL) >> 40) |
           ((x & 0x0000ff0000000000ULL) >> 24) |
           ((x & 0x000000ff00000000ULL) >>  8) |
           ((x & 0x00000000ff000000ULL) <<  8) |
           ((x & 0x0000000000ff0000ULL) << 24) |
           ((x & 0x000000000000ff00ULL) << 40) |
           ((x & 0x00000000000000FFULL) << 56);
}

} // namespace hodea

#endif /*!_HODEA_USWAP_HPP_ */
