// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Retarget printf() and other functions writing to stdout to an UART.
 *
 * This module provides low level functions required to retarget printf()
 * and other functions writing to stdout to an UART. The UART is configured
 * for <baud>:8:N:1, with <baud> determined by the user.
 *
 * This implementation uses busy waiting to output a character to the
 * UART.
 *
 * \author f.hollerer@hodea.org
 */
#if !defined HODEA_STM32_RETARGET_STDOUT_UART_HPP
#define HODEA_STM32_RETARGET_STDOUT_UART_HPP

#include <hodea/core/cstdint.hpp>
#include <hodea/core/math.hpp>
#include <hodea/device/hal/device_setup.hpp>

namespace hodea {

/**
 * Baudrate to initialization value for the baud rate register (BRR).
 */
constexpr uint32_t baud_to_brr(unsigned baudrate)
{
    return math_round_to<uint32_t>(1.0 * config_apb1_pclk_hz / baudrate);
}

/**
 * Initialize UART used for stdout.
 *
 * \param[in] uart
 *      The UART device to which the output shall be redirected.
 * \param[in] brr
 *      Configuration value for the baud rate register (BRR).
 */
void retarget_init(USART_TypeDef* device, uint32_t brr);

/**
 * Shutdown UART used for stdout.
 */
void retarget_deinit();

} // namespace hodea

#endif /*!HODEA_STM32_RETARGET_STDOUT_UART_HPP */
