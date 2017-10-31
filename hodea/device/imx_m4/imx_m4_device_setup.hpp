// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Sets up basic infrastructure for the Cortex-M4 core on IMX processors.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_IMX_M4_DEVICE_SETUP_HPP_
#define _HODEA_IMX_M4_DEVICE_SETUP_HPP_

#include <hodea/device/hal/hal_device_properties.hpp>

#if defined HODEA_DERIVED_CONFIG_BRAND_IMX_M4
#include <device_imx.h>
#else
#error "Unsupported IMX device."
#endif

#endif /*!_HODEA_IMX_M4_DEVICE_SETUP_HPP_ */
