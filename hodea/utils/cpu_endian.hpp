// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Convert between specified byte order and CPU byte order.
 *
 * This module provides functions to convert an unsigned data type
 * with given size and byte order into the same type representing
 * the value in CPU byte order, and vice versa.
 *
 * \note
 * We expect the CPU to user either big or little endian format. We
 * don't support PDP endian.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_CPU_ENDIAN_HPP_
#define _HODEA_CPU_ENDIAN_HPP_

#include <stdint.h>

namespace hodea {

/*
 * We use predefined macros to determine the endianness of the target CPU.
 * Unfortunately, this predefined macros vary from compiler to compiler.
 * If we are unable to determine the endianness, the user must pass
 * the macro HONDEA_IS_CPU_LE with its value set to  true or false 
 * to the compiler via command line.
 */

/*
 * GCC and LLVM/clang provide __BYTE_ORDER__, __ORDER_LITTLE_ENDIAN__
 * and __ORDER_BIG_ENDIAN__.
 */
#if defined __BYTE_ORDER__ && defined __ORDER_LITTLE_ENDIAN__

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define HONDEA_IS_CPU_LE true
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define HONDEA_IS_CPU_LE false
#endif

#endif

/*
 * ARM Compiler V5 or older.
 */
#if defined __CC_ARM
#if defined __BIG_ENDIAN
#define HONDEA_IS_CPU_LE false
#else
#define HONDEA_IS_CPU_LE true
#endif
#endif

/*
 * IAR Compiler
 */
#if defined __ICCARM__
#if __LITTLE_ENDIAN__ == 0
#define HONDEA_IS_CPU_LE false
#elif __LITTLE_ENDIAN__ == 1
#define HONDEA_IS_CPU_LE true
#endif
#endif

#if !defined HONDEA_IS_CPU_LE
#error "Unable to detect cpu endianness via predefined macros."
#error "Please provide HONDEA_IS_CPU_LE = true or false via command line."
#endif

#define HONDEA_IS_CPU_BE (!HONDEA_IS_CPU_LE)

/**
 * Test if CPU uses the little endian format.
 */
constexpr bool is_cpu_le()
{
    return HONDEA_IS_CPU_LE;
}

/**
 * Test if CPU uses the big endian format.
 */
constexpr bool is_cpu_be()
{
    return HONDEA_IS_CPU_BE;
}

} // namespace hodea

#endif /*!_HODEA_CPU_ENDIAN_HPP_ */
