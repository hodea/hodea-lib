// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Sets up basic infrastructure for STM32 devices.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_STM32_DEVICE_SETUP_HPP_
#define _HODEA_STM32_DEVICE_SETUP_HPP_

#include <hodea/device/hal/hal_device_properties.hpp>

#if defined HODEA_DERIVED_CONFIG_SERIES_STM32F0
#include <stm32f0xx.h>
#elif defined HODEA_DERIVED_CONFIG_SERIES_STM32F3
#include <stm32f3xx.h>
#else
#error "Unsupported STM32 device."
#endif

#endif /*!_HODEA_STM32_DEVICE_SETUP_HPP_ */
