// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Support for configuring the device pins.
 *
 * \author f.hollerer@hodea.org
 */
#if !defined HODEA_HAL_PIN_CONFIG_HPP
#define HODEA_HAL_PIN_CONFIG_HPP

#include <hodea/device/hal/device_properties.hpp>

#if defined HODEA_DERIVED_CONFIG_BRAND_STM32
#include <hodea/device/stm32/pin_config.hpp>
#elif defined HODEA_DERIVED_CONFIG_SERIES_IMX7_M4
#include <hodea/device/imx7_m4/pin_config.hpp>
#else
#error "Unsupported device."
#endif

#endif /*!HODEA_HAL_PIN_CONFIG_HPP */
