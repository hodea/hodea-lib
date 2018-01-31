// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Types and classes supporting low level access to peripheral devices.
 *
 * \author f.hollerer@hodea.org
 */
#if !defined HODEA_ARM_CORTEX_CM_DEVICE_ACCESS_HPP
#define HODEA_ARM_CORTEX_CM_DEVICE_ACCESS_HPP

#include <hodea/core/cstdint.hpp>

/**
 * Template class to represent a pointer to a peripheral device.
 *
 * This class allows to specify the address of a device as integer
 * constant at compile time, and overloads the cast and pointer operator
 * to access the devices its associated pointer type at runtime.
 *
 * Rational:
 *
 * The CMSIS <device.h> header file declares the peripheral address map in
 * terms of base of base addresses, and derives pointers to peripherals
 * from that base addresses.
 * \see http://arm-software.github.io/CMSIS_5/Core/html/device_h_pg.html
 * 
 * Example:
 *
 * \code
 * #define PERIPH_BASE (0x40000000UL)
 * #define TIM0_BASE   (PERIPH_BASE)
 * #define TIM1_BASE   (PERIPH_BASE + 0x0800)
 *
 * #define TIM0 ((TMR_TypeDef *) TIM0_BASE)
 * #define TIM1 ((TMR_TypeDef *) TIM1_BASE)
 * \endcode
 *
 * Usually, the device pointers TIM0, TIM1 etc. are used in the
 * application.
 *
 * Unfortunately, C++ does treat them as pointers rather than integer
 * constants. Therefore, they are not a constant expression.
 *
 * For the following line
 *
 * \code
 * constexpr TMR_TypeDef* tim = TIM0;
 * \endcod
 *
 * gcc gives the error:
 *
 * \verbatim
 * > error: reinterpret_cast from integer to pointer
 * \endverbatim
 *
 * In contrast
 *
 * \code
 * constexpr uinitpr tim = TIM0_BASE;
 * \endcode
 *
 * compiles and is as efficient as macros.
 *
 * This class combines both. It let declare a device using the integer
 * constant:
 *
 * \code
 * constexpr Device_pointer<TMR_TypeDef> tim{TIM0_BASE}
 * \endcode
 *
 * and access its registers via pointer operations.
 *
 * \code
 * tim->CR = 0;
 * \endcode
 */
template <typename T>
class Device_pointer {
public:
    constexpr Device_pointer(uintptr_t addr) : addr{addr} {}

    T* operator->() const
    {
        return reinterpret_cast<T*>(addr);
    }

    operator T*() const
    {
        return reinterpret_cast<T*>(addr);
    }

    const uintptr_t addr;
};

#endif /*!HODEA_ARM_CORTEX_CM_DEVICE_ACCESS_HPP */
