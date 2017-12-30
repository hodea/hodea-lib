// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * CPU related functions.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined HODEA_HAL_CPU_HPP
#define HODEA_HAL_CPU_HPP

#include <hodea/device/hal/device_properties.hpp>

#if defined HODEA_DERIVED_CONFIG_BRAND_STM32
#include <hodea/device/stm32/cpu.hpp>
#elif defined HODEA_DERIVED_CONFIG_BRAND_IMX_M4
#error "imx_m4 not yet supported"
#else
#error "Unsupported device."
#endif

#endif /*!HODEA_HAL_CPU_HPP */
