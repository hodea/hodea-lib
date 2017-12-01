// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Digital input / output.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_HAL_CRITICAL_SECTION_HPP_
#define _HODEA_HAL_CRITICAL_SECTION_HPP_

#include <hodea/device/hal/device_properties.hpp>

#if defined HODEA_DERIVED_CONFIG_CORE_ARM_CORTEX_M
#include <hodea/device/arm_cortex_m/critical_section.hpp>
#else
#error "Unsupported device."
#endif

#endif /*!_HODEA_HAL_CRITICAL_SECTION_HPP_ */
