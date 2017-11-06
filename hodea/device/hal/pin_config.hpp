// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Support for configuring the device pins.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_HAL_PIN_CONFIG_HPP_
#define _HODEA_HAL_PIN_CONFIG_HPP_

#include <hodea/device/hal/device_properties.hpp>

#if defined HODEA_DERIVED_CONFIG_BRAND_STM32
#include <hodea/device/stm32/pin_config.hpp>
#elif defined HODEA_DERIVED_CONFIG_SERIES_IMX7_M4
#include <hodea/device/imx7_m4/pin_config.hpp>
#else
#error "Unsupported device."
#endif

#endif /*!_HODEA_HAL_PIN_CONFIG_HPP_ */
