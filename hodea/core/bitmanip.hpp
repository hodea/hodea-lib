// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Functions for bit manipulation.
 *
 * This file provides several template functions for bit manipulation,
 * e.g. to set, clear or test a bit (or multiple bits) within a variable
 * or peripheral registers.
 *
 * Rational: This functions are more readable than the bit operators
 * provided by the C++ languages. Furthermore, bit operations are prone to
 * side effects caused by integer propagation. We ensure to perform the
 * operations on unsigned types to avoid problems caused by integer
 * propagation.
 *
 * \note
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
 * The text and example above is from the MISRA C 2012 standard. Another
 * example is:
 *
 * \code
 * unsigned v = 0;
 * int8_t m = 0xff;
 *
 * v |= m; // on 32-bit machine: v gets 0xffffffff instead of 0xff
 * endcode
 *
 * In this example the variable \a m has the wrong type in first place.
 * But we want our bit manipulation functions to behave reasonable as
 * they don't introduce any constrains on the types with which they are
 * used.
 *
 * \author f.hollerer@hodea.org
 */
#if !defined HODEA_BITMANIP_HPP
#define HODEA_BITMANIP_HPP

#include <type_traits>
#include <hodea/core/type_constraints.hpp>

namespace hodea {

/**
 * Type to specify the value of a bit.
 *
 * A bit can be '0' or '1'. This is best expressed by a boolean type.
 */
typedef bool Bit_value;

/**
 * Construct bitmask with a single bit set for a given bit position.
 */
template <
    typename T = unsigned,
    typename = typename enable_if_integral_type<T>::type
    >
constexpr T bit_to_msk(int pos)
{
    return (static_cast<T>(1) << pos);
}

/**
 * Construct a bitmask based on its position and its length.
 */
template <
    typename T,
    typename = typename enable_if_integral_type<T>::type
    >
constexpr T bitmask(int pos, int num_bits = 1)
{
    return
        (static_cast<T>(1) << pos) |
        ((num_bits > 1) ? bitmask<T>(pos + 1, num_bits - 1) : 0);
}

/**
 * Clear a single bit or multiple bits.
 *
 * \param[in,out] var
 *      Reference to the variable where to clear the bit(s).
 * \param[in] msk
 *      Bitmask selecting the bit(s) to clear.
 *
 * \note
 * \a var can also be a peripheral device register qualified volatile.
 */
template <
    typename T_v, typename T_m,
    typename = typename std::enable_if<std::is_integral<T_v>::value>::type,
    typename = typename enable_if_integral_type<T_v>::type,
    typename = typename enable_if_bitmask_type<T_m>::type
    >
void clr_bit(T_v& var, T_m msk)
{
    static_cast<typename std::make_unsigned<T_v>::type &>(var) &=
        ~static_cast<typename std::make_unsigned<T_m>::type>(msk);
}

/**
 * Set a single bit or multiple bits.
 *
 * \param[in,out] var
 *      Reference to the variable where to set the bit(s).
 * \param[in] msk
 *      Bitmask selecting the bit(s) to set.
 *
 * \note
 * \a var can also be a peripheral device register qualified volatile.
 */
template <
    typename T_v, typename T_m,
    typename = typename enable_if_integral_type<T_v>::type,
    typename = typename enable_if_bitmask_type<T_m>::type
    >
void set_bit(T_v& var, T_m msk)
{
    static_cast<typename std::make_unsigned<T_v>::type &>(var) |=
        static_cast<typename std::make_unsigned<T_m>::type>(msk);
}

/**
 * Set a single bit or multiple bits to a given value.
 *
 * \param[in,out] var
 *      Reference to the variable where to set or clear bit(s).
 * \param[in] msk
 *      Bitmask selecting the bit(s).
 * \param[in] val
 *      The new value for the selected bit(s). If 0 (false) the selected
 *      bit(s) is/are cleared, otherwise set.
 *
 * \note
 * \a var can also be a peripheral device register qualified volatile.
 */
template <
    typename T_v, typename T_m,
    typename = typename enable_if_integral_type<T_v>::type,
    typename = typename enable_if_bitmask_type<T_m>::type
    >
void set_bit_value(T_v& var, T_m msk, Bit_value val)
{
    if (val)
        set_bit(var, msk);
    else
        clr_bit(var, msk);
}

/**
 * Modify bits while avoiding multiple read-modify-write cycles.
 *
 * This function can be used to updated several bits at once by clearing
 * and setting them accordingly.
 *
 * It reads \a var at the begin of functions, and writes it back after
 * applying the clear and set operations.
 *
 * For the bit operations it first clears all bits as specified in
 * \a clr_msk,
 * and then sets the bits given in \a set_msk.
 *
 * Rational: \a var can be a peripheral device register qualified volatile.
 * Using \a clr_bit() and \a set_bit() in series would result in multiple
 * read-modify-write cycles, with each access effecting the functioning
 * of the hardware. Ensuring that the \var is only read and written
 * once we avoid this problem.
 *
 * \param[in,out] var
 *      Reference to the variable where to clear and set bit(s).
 * \param[in] clr_msk
 *      Bitmask selecting the bit(s) to clear.
 * \param[in] set_msk
 *      Bitmask selecting the bit(s) to set.
 *
 * \note
 * \a var can also be a peripheral device register qualified volatile.
 */
template <
    typename T_v, typename T_cm, typename T_sm,
    typename = typename enable_if_integral_type<T_v>::type,
    typename = typename enable_if_bitmask_type<T_cm>::type,
    typename = typename enable_if_bitmask_type<T_sm>::type
    >
void modify_bits(
    T_v& var, T_cm clr_msk, T_sm set_msk
    )
{
    typename std::remove_volatile<
        typename std::make_unsigned<T_v>::type>::type uvar;

    uvar = var;

    // volatile qualifier is removed, we can use clr_bit() and set_bit()
    clr_bit(uvar, clr_msk);
    set_bit(uvar, set_msk);

    var = uvar;
}

/**
 * Toggle a single bit or multiple bits.
 *
 * \param[in,out] var
 *      Reference to the variable where to toggle the bit(s).
 * \param[in] msk
 *      Bitmask selecting the bit(s) to toggle.
 *
 * \note
 * \a var can also be a peripheral device register qualified volatile.
 */
template <
    typename T_v, typename T_m,
    typename = typename enable_if_integral_type<T_v>::type,
    typename = typename enable_if_bitmask_type<T_m>::type
    >
void toggle_bit(T_v& var, T_m msk)
{
    static_cast<typename std::make_unsigned<T_v>::type &>(var) ^=
        static_cast<typename std::make_unsigned<T_m>::type>(msk);
}

/**
 * Test if a single bit or several bits are set.
 *
 * \param[in] value
 *      The value to test.
 * \param[in] msk
 *      Bitmask selecting a single bit or multiple bits to test.
 * \param[in] need_all_bits_set
 *      This parameter controls the test method. If \a need_all_bits_set
 *      is true all selected bits must be set for the test to evaluate to
 *      true. Otherwise if \a need_all_bits_set is false at least one of
 *      the selected bits must be set for the test to evaluate to true.
 *      Default: need_all_bits_set = false.
 *
 * \returns
 *      Returns true if bits are set according the selected test method,
 *      false otherwise.
 */
template <
    typename T_v, typename T_m,
    typename = typename enable_if_integral_type<T_v>::type,
    typename = typename enable_if_bitmask_type<T_m>::type
    >
bool is_bit_set(T_v val, T_m msk, bool need_all_bits_set = false)
{
    typename std::remove_volatile<
        typename std::make_unsigned<T_v>::type>::type uval = val;

    using msk_unsigned_t = typename std::make_unsigned<T_m>::type;
    msk_unsigned_t umsk = static_cast<msk_unsigned_t>(msk);

    return (need_all_bits_set) ? ((uval & umsk) == umsk) : (uval & umsk);
}

} // namespace hodea

#endif /*!HODEA_BITMANIP_HPP */
