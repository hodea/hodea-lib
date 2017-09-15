// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Support functions for bit fields.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_BITFIELD_HPP_
#define _HODEA_BITFIELD_HPP_

#include <hodea/core/cstdint.hpp>

namespace hodea {

/**
 * Construct a bit field from its value and position.
 *
 * This functions shifts a value to a desired position for assigning the
 * result to a variable are peripheral register consisting of several bit
 * fields.
 *
 * \param[in] val
 *      The value for the bit field to construct.
 * \param[in] pos
 *      The bit position of the first bit of the bit field within \a val.
 *
 * \returns
 *      Bit field according the given value and position
 */
static inline constexpr uint_fast32_t val2fld(uint_fast32_t value, int pos)
{
    return value << pos;
}

/**
 * Construct a bit field from its value, its bit position and mask.
 *
 * This functions shifts and masks a value for assigning the result to a
 * variable are peripheral register consisting of several bit fields.
 *
 * \param[in] val
 *      The value for the bit field to construct.
 * \param[in] pos
 *      The bit position of the first bit of the bit field within \a val.
 * \param[in] msk
 *      The bit mask for the bit field. The mask defines the size of
 *      the field.
 *
 * \returns
 *      Bit field according the given value, position and mask.
 *
 * \note
 * We expect \a value and \a msk to be the same type.
 */
static inline constexpr uint_fast32_t val2fld(
    uint_fast32_t value, int pos, uint_fast32_t msk
    )
{
    return (value << pos) & msk;
}

/**
 * Extract value from a bit field based on its position and mask.
 *
 * This functions masks and shifts a bit field for extracting its
 * value from a variable are peripheral register consisting of
 * several bit fields.
 *
 * \param[in] field
 *      Variable or register content from which to extract the field.
 * \param[in] msk
 *      The bit mask for the bit field. The mask defines the size of
 *      the field.
 * \param[in] pos
 *      The bit position of the first bit of bit field within \a val.
 *
 * \returns
 *      The bit field value extracted from \a field
 *
 * \note
 * We expect \a field and \a msk to be the same type.
 */
static inline constexpr uint_fast32_t fld2val(
    uint_fast32_t field, int pos, uint_fast32_t msk
    )
{
    return (field & msk) >> pos;
}

} // namespace hodea

#endif /*!_HODEA_BITFIELD_HPP_ */
