// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Digital input / output.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined HODEA_HAL_DIGIO_HPP
#define HODEA_HAL_DIGIO_HPP

#include <hodea/device/hal/device_properties.hpp>

#if defined HODEA_DERIVED_CONFIG_BRAND_STM32
#include <hodea/device/stm32/digio.hpp>
#elif defined HODEA_DERIVED_CONFIG_BRAND_IMX_M4
#include <hodea/device/imx_m4/digio.hpp>
#else
#error "Unsupported device."
#endif

#endif /*!HODEA_HAL_DIGIO_HPP */
