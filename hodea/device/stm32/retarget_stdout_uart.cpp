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
 * \author f.hollerer@gmx.net
 */
#include <hodea/core/cstdint.hpp>
#include <hodea/core/bitmanip.hpp>
#include <hodea/device/hal/device_setup.hpp>
#include "retarget_stdout_uart.hpp"

using namespace hodea;

static USART_TypeDef* device;

void hodea::retarget_init(USART_TypeDef* uart, uint32_t brr)
{
    device = uart;

    device->CR1 = USART_CR1_TE;
    device->BRR = brr;
    set_bit(device->CR1, USART_CR1_UE);
}

/**
 * Shutdown UART used for stdout.
 */
void hodea::retarget_deinit()
{
    device->CR1 = 0;
}

#if defined __GNUC__

extern "C" int _write (int, char *buffer, int size);
int _write (int, char *buffer, int size)
{
    if (buffer == nullptr)
        return -1;

    for (int i = 0; i < size; i++) {
        while (!is_bit_set(device->ISR, USART_ISR_TXE)) ;
        device->TDR = buffer[i];
    }
    return size;
}

#elif defined __ARMCC_VERSION && (__ARMCC_VERSION >= 6010050)

#include <stdio.h>

extern "C" {

__asm(".global __use_no_semihosting\n\t");

struct __FILE { int handle; };
FILE __stdout;

int sendchar(int ch)
{
    device->TDR = ch;
    while (!is_bit_set(device->ISR, USART_ISR_TXE)) {
        ;
    }
    return ch;
}

int fputc(int ch, FILE* f)
{
    return sendchar(ch);
}

int ferror(FILE* f)
{
    return EOF;
}

void _ttywrch(int ch)
{
    sendchar (ch);
}


void _sys_exit(int return_code)
{
  while (1) ;   /* endless loop */
}

} // extern "C"

#endif

