// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Functions to help with serialization and de-serialization.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_BYTEORDER_HPP_
#define _HODEA_BYTEORDER_HPP_

#include <stdint.h>

namespace hodea {

/**
 * Extract a 8 bit number.
 *
 * param[out] dst Target variable.
 * param[in] buf  Source buffer holding the number.
 *
 * \returns
 *      The number of bytes read from \a buf.
 */
template <typename T>
unsigned fetch8(T& dst, const uint8_t *buf)
{
    uint8_t v;

    v = *buf;
    dst = v;
    return sizeof(v);
}

/**
 * Extract a 16 bit number stored in little endian format (LSB first).
 *
 * param[out] dst Target variable.
 * param[in] buf  Source buffer holding the number.
 *
 * \returns
 *      The number of bytes read from \a buf.
 */
template <typename T>
unsigned fetch16_le(T& dst, const uint8_t *buf)
{
    uint16_t v;

    v = (static_cast<uint16_t>(buf[1]) << 8) | buf[0];
    dst = v;
    return sizeof(v);
}

/**
 * Extract a 32 bit number stored in little endian format (LSB first).
 *
 * param[out] dst Target variable.
 * param[in] buf  Source buffer holding the number.
 *
 * \returns
 *      The number of bytes read from \a buf.
 */
template <typename T>
unsigned fetch32_le(T& dst, const uint8_t *buf)
{
    uint32_t v;

    v = (static_cast<uint32_t>(buf[3]) << 24) |
        (static_cast<uint32_t>(buf[2]) << 16) |
        (static_cast<uint32_t>(buf[1]) << 8)  |
        buf[0];

    dst = v;
    return sizeof(v);
}

/**
 * Extract a 16 bit number stored in big endian format (MSB first).
 *
 * param[out] dst Target variable.
 * param[in] buf  Source buffer holding the number.
 *
 * \returns
 *      The number of bytes read from \a buf.
 */
template <typename T>
unsigned fetch16_be(T& dst, const uint8_t *buf)
{
    uint16_t v;

    v = (static_cast<uint16_t>(buf[0]) << 8) | buf[1];
    dst = v;
    return sizeof(v);
}

/**
 * Extract a 32 bit number stored in big endian format (MSB first).
 *
 * param[out] dst Target variable.
 * param[in] buf  Source buffer holding the number.
 *
 * \returns
 *      The number of bytes read from \a buf.
 */
template <typename T>
unsigned fetch32_be(T& dst, const uint8_t *buf)
{
    uint32_t v;

    v = (static_cast<uint32_t>(buf[0]) << 24) |
        (static_cast<uint32_t>(buf[1]) << 16) |
        (static_cast<uint32_t>(buf[2]) << 8)  |
        buf[3];

    dst = v;
    return sizeof(v);
}

/**
 * Store a 8 bit number.
 *
 * param[out] buf Target buffer.
 * param[in] src  Source variable.
 *
 * \returns
 *      The number of bytes written to \a buf.
 */
template <typename T>
unsigned store8(uint8_t *buf, const T src)
{
    uint8_t v = static_cast<uint8_t>(src);

    *buf = v;
    return sizeof(v);
}

} // namespace hodea

#endif /*!_HODEA_BYTEORDER_HPP_ */
