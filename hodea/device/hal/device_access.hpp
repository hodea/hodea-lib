// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Types and classes supporting low level access to peripheral devices.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined HODEA_HAL_DEVICE_ACCESS_HPP
#define HODEA_HAL_DEVICE_ACCESS_HPP

#include <hodea/device/hal/device_properties.hpp>

#if defined HODEA_DERIVED_CONFIG_BRAND_STM32
#include <hodea/device/stm32/device_access.hpp>
#elif defined HODEA_DERIVED_CONFIG_BRAND_IMX_M4
#include <hodea/device/imx_m4/device_access.hpp>
#else
#error "Unsupported device."
#endif

#endif /*!HODEA_HAL_DEVICE_ACCESS_HPP */
