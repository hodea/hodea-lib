// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Sets up basic infrastructure for STM32 devices.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined HODEA_STM32_DEVICE_SETUP_HPP
#define HODEA_STM32_DEVICE_SETUP_HPP

#include <hodea/device/hal/device_properties.hpp>
#include "hodea_user_config.hpp"

#if defined HODEA_DERIVED_CONFIG_SERIES_STM32F0
#include <stm32f0xx.h>
#elif defined HODEA_DERIVED_CONFIG_SERIES_STM32F3
#include <stm32f3xx.h>
#else
#error "Unsupported STM32 device."
#endif

#include <hodea/device/hal/device_access.hpp>

#endif /*!HODEA_STM32_DEVICE_SETUP_HPP */
