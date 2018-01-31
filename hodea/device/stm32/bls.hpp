// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Bootloader support functions for STM32 devices.
 *
 * \author f.hollerer@hodea.org
 */
#if !defined HODEA_STM32_BLS_HPP
#define HODEA_STM32_BLS_HPP

#include <hodea/core/cstdint.hpp>

namespace hodea {

/**
 * Calculate CRC over program memory.
 *
 * This function uses the built-in CRC unit and DMA channel 1 to
 * calculate the CRC value over the given program memory.
 *
 * The used CRC has the following properties:
 *   Width        = 32
 *   Poly         = 0x4C11DB7
 *   XorIn        = 0xffffffff
 *   ReflectIn    = False
 *   XorOut       = 0
 *   ReflectOut   = False
 *
 * \param[in] start
 *      Start address for CRC calculation.
 * \param[in] end
 *      End address for CRC calculation.
 *
 * @returns
 *      CRC calculated from \a start to \a end (inclusive).
 */
uint32_t bls_progmem_crc(const uint32_t *start, const uint32_t *end);

} // namespace hodea

#endif /*!HODEA_STM32_BLS_HPP */
