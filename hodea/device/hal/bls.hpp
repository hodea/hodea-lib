// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Bootloader support functions.
 *
 * \author f.hollerer@hodea.org
 */
#if !defined HODEA_HAL_BLS_HPP
#define HODEA_HAL_BLS_HPP

#include <hodea/device/hal/device_properties.hpp>

#if defined HODEA_DERIVED_CONFIG_BRAND_STM32
#include <hodea/device/stm32/bls.hpp>
#elif defined HODEA_DERIVED_CONFIG_BRAND_IMX_M4
#error "imx_m4 not yet supported"
#else
#error "Unsupported device."
#endif

#endif /*!HODEA_HAL_BLS_HPP */
