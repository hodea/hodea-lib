// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Sets up basic infrastructure for the Cortex-M4 core on IMX processors.
 *
 * \author f.hollerer@hodea.org
 */
#if !defined HODEA_IMX_M4_DEVICE_SETUP_HPP
#define HODEA_IMX_M4_DEVICE_SETUP_HPP

#include <hodea/device/hal/device_properties.hpp>

#if defined HODEA_DERIVED_CONFIG_BRAND_IMX_M4
#include <device_imx.h>
#else
#error "Unsupported IMX device."
#endif

#include <hodea/device/hal/device_access.hpp>

#endif /*!HODEA_IMX_M4_DEVICE_SETUP_HPP */
