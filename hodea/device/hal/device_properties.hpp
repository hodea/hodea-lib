// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Derive properties from selected target device.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_HAL_DEVICE_PROPERTIES_HPP_
#define _HODEA_HAL_DEVICE_PROPERTIES_HPP_

#if defined(STM32F030x6) || defined(STM32F030x8) || \
    defined(STM32F031x6) || defined(STM32F038xx) || \
    defined(STM32F042x6) || defined(STM32F048xx) || \
    defined(STM32F051x8) || defined(STM32F058xx) || \
    defined(STM32F070x6) || defined(STM32F070xB) || \
    defined(STM32F071xB) || defined(STM32F072xB) || \
    defined(STM32F078xx) || defined(STM32F091xC) || \
    defined(STM32F098xx) || defined(STM32F030xC)

#define HODEA_DERIVED_CONFIG_BRAND_STM32
#define HODEA_DERIVED_CONFIG_SERIES_STM32F0
#define HODEA_DERIVED_CONFIG_CORE_ARM_CORTEX_M0

#elif defined(STM32F301x8) || defined(STM32F302x8) || \
      defined(STM32F302xC) || defined(STM32F302xE) || \
      defined(STM32F303x8) || defined(STM32F303xC) || \
      defined(STM32F303xE) || defined(STM32F373xC) || \
      defined(STM32F334x8) || defined(STM32F318xx) || \
      defined(STM32F328xx) || defined(STM32F358xx) || \
      defined(STM32F378xx) || defined(STM32F398xx)

#define HODEA_DERIVED_CONFIG_BRAND_STM32
#define HODEA_DERIVED_CONFIG_SERIES_STM32F3
#define HODEA_DERIVED_CONFIG_CORE_ARM_CORTEX_M4

#elif defined(CPU_MCIMX7D_M4)

#define HODEA_DERIVED_CONFIG_BRAND_IMX_M4
#define HODEA_DERIVED_CONFIG_SERIES_IMX7_M4
#define HODEA_DERIVED_CONFIG_CORE_ARM_CORTEX_M4

#else
#error "Unsupported device."
#endif

#if defined HODEA_DERIVED_CONFIG_CORE_ARM_CORTEX_M0 || \
    defined HODEA_DERIVED_CONFIG_CORE_ARM_CORTEX_M4

#define HODEA_DERIVED_CONFIG_CORE_ARM_CORTEX_M

#endif

#endif /*!_HODEA_HAL_DEVICE_PROPERTIES_HPP_ */
