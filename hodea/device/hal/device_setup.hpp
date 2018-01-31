// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Set up basic infrastructure for a device.
 *
 * \author f.hollerer@hodea.org
 */
#if !defined HODEA_HAL_DEVICE_SETUP_HPP
#define HODEA_HAL_DEVICE_SETUP_HPP

#include <hodea/device/hal/device_properties.hpp>

#if defined HODEA_DERIVED_CONFIG_BRAND_STM32
#include <hodea/device/stm32/device_setup.hpp>
#elif defined HODEA_DERIVED_CONFIG_BRAND_IMX_M4
#include <hodea/device/imx_m4/device_setup.hpp>
#else
#error "Unsupported device."
#endif

#endif /*!HODEA_HAL_DEVICE_SETUP_HPP */
