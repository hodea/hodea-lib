// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Types and classes supporting low level access to peripheral devices.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined HODEA_IMX_M4_DEVICE_ACCESS_HPP
#define HODEA_IMX_M4_DEVICE_ACCESS_HPP

#include <hodea/device/arm_cortex_m/device_access.hpp>

/**
 * Mask and shift a bit field value for use in a register bit range.
 *
 * \param[in] field  Name of the register bit field.
 * \param[in] value  Value of the bit field.
 *
 * \return           Masked and shifted value.
 *
 * \note
 * The CMSIS standard introduced the _VAL2FLD() macro to shift a value to
 * the correct field position. But this requires that the chip vendor
 * suffixes the fields according the standard with _Pos and _Msk.
 *
 * Unfortunately, NXP is not following the standard. Instead, NXP suffixes
 * the fields with _SHIFT and _MASK.
 *
 * Therefore, we provide our own implementation of the _VAL2FLD()
 * macro for NXP.
 */
#define _NXP_VAL2FLD(field, value) \
    (((value) << field ## _SHIFT) & field ## _MASK)

/**
 * Mask and shift a register value to extract a bit field value.
 *
 * \param[in] field  Name of the register bit field.
 * \param[in] value  Value of the bit field.
 *
 * \return           Masked and shifted bit field value.
 *
 * \note
 * The CMSIS standard introduced the _FLD2VAL() macro to extract a
 * bit field value from a register value. But this requires that the chip
 * vendor to suffixes the fields according the standard with _Pos and _Msk.
 *
 * Unfortunately, NXP is not following the standard. Instead, NXP suffixes
 * the fields with _SHIFT and _MASK.
 *
 * Therefore, we provide our own implementation of the _FLD2VAL()
 * macro for NXP.
 */
#define _NXP_FLD2VAL(field, value) \
    (((value) & field ## _MASK) >> field ## _SHIFT)

#endif /*!HODEA_IMX_M4_DEVICE_ACCESS_HPP */
