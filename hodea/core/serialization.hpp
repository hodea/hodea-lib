// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Functions to serialize and deserialize numbers in different byte order.
 *
 * Example for serialization:
 *
 * \code
 * uint8_t buf[100];
 * uint16_t v1 = 0x4711;
 * uint16_ v2 = 0xcafe;
 * :
 * uint8_t *p = buf;
 * p += store16_le(p, v1);
 * p += store16_le(p, v2);
 * :
 * send_msg(buf, p - buf);
 * \endcode
 *
 * Example for deserialization:
 *
 * \code
 * uint8_t buf[100];
 * uint8_t *p;
 * uint16_t v1;
 * uint16_t v2;
 * :
 * recv_msg(buf, ...);
 * :
 * uint8_t *p = buf;
 * p += fetch16(v1, buf);
 * p += fetch16(v2, buf);
 * \endcode
 *
 * @note
 * The function parameters are in the same order as used by memcpy() and
 * strcpy() library functions, i.e. the first parameter gives the
 * destination, the second the source.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_SERIALIZATION_HPP_
#define _HODEA_SERIALIZATION_HPP_

#include <hodea/core/cstdint.hpp>

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
template <
    typename T,
    typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
int fetch8(T& dst, const uint8_t *buf)
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
template <
    typename T,
    typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
int fetch16_le(T& dst, const uint8_t *buf)
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
template <
    typename T,
    typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
int fetch32_le(T& dst, const uint8_t *buf)
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
 * Extract a 64 bit number stored in little endian format (LSB first).
 *
 * param[out] dst Target variable.
 * param[in] buf  Source buffer holding the number.
 *
 * \returns
 *      The number of bytes read from \a buf.
 */
template <
    typename T,
    typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
int fetch64_le(T& dst, const uint8_t *buf)
{
    uint64_t v;

    v = (static_cast<uint64_t>(buf[7]) << 56) |
        (static_cast<uint64_t>(buf[6]) << 48) |
        (static_cast<uint64_t>(buf[5]) << 40) |
        (static_cast<uint64_t>(buf[4]) << 32) |
        (static_cast<uint64_t>(buf[3]) << 24) |
        (static_cast<uint64_t>(buf[2]) << 16) |
        (static_cast<uint64_t>(buf[1]) << 8)  |
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
template <
    typename T,
    typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
int fetch16_be(T& dst, const uint8_t *buf)
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
template <
    typename T,
    typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
int fetch32_be(T& dst, const uint8_t *buf)
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
 * Extract a 64 bit number stored in big endian format (MSB first).
 *
 * param[out] dst Target variable.
 * param[in] buf  Source buffer holding the number.
 *
 * \returns
 *      The number of bytes read from \a buf.
 */
template <
    typename T,
    typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
int fetch64_be(T& dst, const uint8_t *buf)
{
    uint64_t v;

    v = (static_cast<uint64_t>(buf[0]) << 56) |
        (static_cast<uint64_t>(buf[1]) << 48) |
        (static_cast<uint64_t>(buf[2]) << 40) |
        (static_cast<uint64_t>(buf[3]) << 32) |
        (static_cast<uint64_t>(buf[4]) << 24) |
        (static_cast<uint64_t>(buf[5]) << 16) |
        (static_cast<uint64_t>(buf[6]) << 8)  |
        buf[7];

    dst = v;
    return sizeof(v);
}

/**
 * Store a 8 bit number.
 *
 * param[out] buf Target buffer.
 * param[in] val The value to store.
 *
 * \returns
 *      The number of bytes written into \a buf.
 */
template <
    typename T,
    typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
int store8(uint8_t *buf, const T val)
{
    const uint8_t uval = val;

    *buf = uval;
    return sizeof(uval);
}

/**
 * Store a 16 bit number in little endian format (LSB first).
 *
 * param[out] buf Target buffer.
 * param[in] val The value to store.
 *
 * \returns
 *      The number of bytes written into \a buf.
 */
template <
    typename T,
    typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
int store16_le(uint8_t *buf, const T val)
{
    const uint16_t uval = val;

    buf[0] = uval & 0xffU;
    buf[1] = (uval >> 8) & 0xffU;
    return sizeof(uval);
}

/**
 * Store a 32 bit number in little endian format (LSB first).
 *
 * param[out] buf Target buffer.
 * param[in] val The value to store.
 *
 * \returns
 *      The number of bytes written into \a buf.
 */
template <
    typename T,
    typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
static inline int store32_le(uint8_t *buf, const T val)
{
    const uint32_t uval = val;

    buf[0] = uval & 0xffU;
    buf[1] = (uval >> 8) & 0xffU;
    buf[2] = (uval >> 16) & 0xffU;
    buf[3] = (uval >> 24) & 0xffU;
    return sizeof(uval);
}

/**
 * Store a 64 bit number in little endian format (LSB first).
 *
 * param[out] buf Target buffer.
 * param[in] val The value to store.
 *
 * \returns
 *      The number of bytes written into \a buf.
 */
template <
    typename T,
    typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
static inline int store64_le(uint8_t *buf, const T val)
{
    const uint64_t uval = val;

    buf[0] = uval & 0xffU;
    buf[1] = (uval >> 8) & 0xffU;
    buf[2] = (uval >> 16) & 0xffU;
    buf[3] = (uval >> 24) & 0xffU;
    buf[4] = (uval >> 32) & 0xffU;
    buf[5] = (uval >> 40) & 0xffU;
    buf[6] = (uval >> 48) & 0xffU;
    buf[7] = (uval >> 56) & 0xffU;
    return sizeof(uval);
}

/**
 * Store a 16 bit number in big endian format (MSB first).
 *
 * param[out] buf Target buffer.
 * param[in] val The value to store.
 *
 * \returns
 *      The number of bytes written into \a buf.
 */
template <
    typename T,
    typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
int store16_be(uint8_t *buf, const T val)
{
    const uint16_t uval = val;

    buf[1] = uval & 0xffU;
    buf[0] = (uval >> 8) & 0xffU;
    return sizeof(uval);
}

/**
 * Store a 32 bit number in big endian format (MSB first).
 *
 * param[out] buf Target buffer.
 * param[in] val The value to store.
 *
 * \returns
 *      The number of bytes written into \a buf.
 */
template <
    typename T,
    typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
static inline int store32_be(uint8_t *buf, const T val)
{
    const uint32_t uval = val;

    buf[3] = uval & 0xffU;
    buf[2] = (uval >> 8) & 0xffU;
    buf[1] = (uval >> 16) & 0xffU;
    buf[0] = (uval >> 24) & 0xffU;
    return sizeof(uval);
}

/**
 * Store a 64 bit number in big endian format (MSB first).
 *
 * param[out] buf Target buffer.
 * param[in] val The value to store.
 *
 * \returns
 *      The number of bytes written into \a buf.
 */
template <
    typename T,
    typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
static inline int store64_be(uint8_t *buf, const T val)
{
    const uint64_t uval = val;

    buf[7] = uval & 0xffU;
    buf[6] = (uval >> 8) & 0xffU;
    buf[5] = (uval >> 16) & 0xffU;
    buf[4] = (uval >> 24) & 0xffU;
    buf[3] = (uval >> 32) & 0xffU;
    buf[2] = (uval >> 40) & 0xffU;
    buf[1] = (uval >> 48) & 0xffU;
    buf[0] = (uval >> 56) & 0xffU;
    return sizeof(uval);
}

} // namespace hodea

#endif /*!_HODEA_SERIALIZATION_HPP_ */
