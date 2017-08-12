// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Functions for bit manipulation.
 *
 * This file provides several template functions for bit manipulation,
 * e.g. to set, clear or test a bit (or multiple bits) within a variable.
 *
 * The templates ensure that the operations are performed on unsigned
 * types to avoid surprising effects caused by integer propagation.
 *
 * @note
 * Integer promotion arising when bitwise operators are applied to small
 * unsigned types can lead to confusion. For example a bitwise complement
 * operation on an operand of type unsigned char will generally yield a
 * result of type (signed) int with a negative value.
 *
 * \code
 * u8a = 0xff;
 *
 * if ( ~u8a == 0x00U ) // This test will always fail.
 * \endcode
 *
 * @author f.hollerer@gmx.net
 */
#if !defined _HODEA_BITMANIP_HPP_
#define _HODEA_BITMANIP_HPP_

namespace hodea {

template <typename T_VAR, typename T_MSK>
void clear_bit(T_VAR& var, T_MSK msk)
{
    static_cast<typename std::make_unsigned<T_VAR>::type &>(var) &=
        ~static_cast<typename std::make_unsigned<T_MSK>::type>(msk);
}

} // namespace hodea

#endif /*!_HODEA_BITMANIP_HPP_ */



