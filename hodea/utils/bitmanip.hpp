// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

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
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_BITMANIP_HPP_
#define _HODEA_BITMANIP_HPP_

#include <climits>

namespace hodea {

/**
 * Type to specify the value of a bit.
 *
 * A bit can be '0' or '1'. This is best expressed by a boolean type.
 */
typedef bool Bit_value;

/**
 * Class to construct a bitmask.
 *
 * This class can be used to construct a bitmask.
 *
 * Example:
 * \code
 * unsigned msk = Bitmask<>{}.bit(0).bit(2); // gives 0x5
 * \endcode
 */
template <
    class T = unsigned,
    class = typename std::enable_if<std::is_unsigned<T>::value>::type
    >
class Bitmask{
public:
    constexpr Bitmask(T msk = 0) : msk{msk} {}

    constexpr operator T() const {return msk;}
    
    constexpr Bitmask bit(unsigned pos) const
    {   
        return Bitmask(msk | (Bitmask{1} << pos));
    }   

private:
    T msk;
};

/**
 * Convert bit position to a mask.
 *
 * \param[in] pos Position of a single bit.
 *
 * \returns
 *      Bitmask with the bit in the given position set.
 */
template <typename T = unsigned>
constexpr T bit_to_msk(unsigned pos)
{
    return T{1} << pos;
}

/**
 * Clear a single bit or multiple bits in a variable.
 *
 * \param[in,out] var
 *      Reference to the variable where to clear the bit(s).
 * \param[in] msk
 *      Bitmask selecting the bit(s) to clear.
 *
 * \note
 * \a var can also be a peripheral device register qualified volatile.
 */
template <typename T_VAR, typename T_MSK>
void clr_bit(T_VAR& var, T_MSK msk)
{
    static_cast<typename std::make_unsigned<T_VAR>::type &>(var) &=
        ~static_cast<typename std::make_unsigned<T_MSK>::type>(msk);
}

/**
 * Set a single bit or multiple bits in a variable.
 *
 * \param[in,out] var
 *      Reference to the variable where to set the bit(s).
 * \param[in] msk
 *      Bitmask selecting the bit(s) to set.
 *
 * \note
 * \a var can also be a peripheral device register qualified volatile.
 */
template <typename T_VAR, typename T_MSK>
void set_bit(T_VAR& var, T_MSK msk)
{
    static_cast<typename std::make_unsigned<T_VAR>::type &>(var) |=
        static_cast<typename std::make_unsigned<T_MSK>::type>(msk);
}

/**
 * Set bit(s) to a given value.
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
template <typename T_VAR, typename T_MSK>
void set_bit_value(T_VAR& var, T_MSK msk, Bit_value val)
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
template <typename T_VAR, typename T_CLR_MSK, typename T_SET_MSK>
void modify_bits(
    T_VAR& var, T_CLR_MSK clr_msk, T_SET_MSK set_msk
    )
{
    typename std::remove_volatile<
        typename std::make_unsigned<T_VAR>::type>::type uvar;

    uvar = var;

    // volatile qualifier is removed, we can use clr_bit() and set_bit()
    clr_bit(uvar, clr_msk);
    set_bit(uvar, set_msk);

    var = uvar;
}

/**
 * Test if at lease one of the given bits is set.
 *
 * \param[in] value
 *      The value to tests for the given bit(s).
 * \param[in] msk
 *      Bitmask selecting the bit(s) to test.
 *
 * \returns
 *      Returns true if at least one of the bits specified in \a msk
 *      is set in \a val, false otherwise.
 */
template <typename T_VALUE, typename T_MSK>
bool is_bit_set(T_VALUE val, T_MSK msk)
{
    typename std::remove_volatile<
        typename std::make_unsigned<T_VALUE>::type>::type uval = val;
    typename std::make_unsigned<T_MSK>::type umsk = msk;
   
    return (uval & umsk);
}

/**
 * Test if all of the given bits are set.
 *
 * \param[in] value
 *      The value to tests for the given bit(s).
 * \param[in] msk
 *      Bitmask selecting the bit(s) to test.
 *
 * \returns
 *      Returns true if all bits specified in \a msk are set in \a val,
 *      false otherwise.
 */
template <typename T_VALUE, typename T_MSK>
bool are_all_bits_set(T_VALUE val, T_MSK msk)
{
    typename std::remove_volatile<
        typename std::make_unsigned<T_VALUE>::type>::type uval = val;
    typename std::make_unsigned<T_MSK>::type umsk = msk;
   
    return ((uval & umsk) == umsk);
}

} // namespace hodea

#endif /*!_HODEA_BITMANIP_HPP_ */
