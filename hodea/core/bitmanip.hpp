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
#if !defined _HODEA_BIT_MANIP_HPP_
#define _HODEA_BIT_MANIP_HPP_

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
    
    constexpr Bitmask bit(int pos) const
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
template <
    typename T = unsigned,
    typename = typename std::enable_if<std::is_integral<T>::value>::type
    >
constexpr T bit_to_msk(int pos)
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
template <
    typename T_V, typename T_M,
    typename = typename std::enable_if<std::is_integral<T_V>::value>::type,
    typename = typename std::enable_if<std::is_integral<T_M>::value>::type
    >
void clr_bit(T_V& var, T_M msk)
{
    static_cast<typename std::make_unsigned<T_V>::type &>(var) &=
        ~static_cast<typename std::make_unsigned<T_M>::type>(msk);
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
template <
    typename T_V, typename T_M,
    typename = typename std::enable_if<std::is_integral<T_V>::value>::type,
    typename = typename std::enable_if<std::is_integral<T_M>::value>::type
    >
void set_bit(T_V& var, T_M msk)
{
    static_cast<typename std::make_unsigned<T_V>::type &>(var) |=
        static_cast<typename std::make_unsigned<T_M>::type>(msk);
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
    typename T_V, typename T_M,
    typename = typename std::enable_if<std::is_integral<T_V>::value>::type,
    typename = typename std::enable_if<std::is_integral<T_M>::value>::type
    >
void set_bit_value(T_V& var, T_M msk, Bit_value val)
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
    typename T_V, typename T_CM, typename T_SM,
    typename = typename std::enable_if<std::is_integral<T_V>::value>::type,
    typename = typename std::enable_if<std::is_integral<T_CM>::value>::type,
    typename = typename std::enable_if<std::is_integral<T_SM>::value>::type
    >
void modify_bits(
    T_V& var, T_CM clr_msk, T_SM set_msk
    )
{
    typename std::remove_volatile<
        typename std::make_unsigned<T_V>::type>::type uvar;

    uvar = var;

    // volatile qualifier is removed, we can use clr_bit() and set_bit()
    clr_bit(uvar, clr_msk);
    set_bit(uvar, set_msk);

    var = uvar;
}

/**
 * Test if all the specified bits are set.
 *
 * \param[in] value
 *      The value to test.
 * \param[in] msk
 *      Bitmask selecting a single bit or multiple bits to test.
 *
 * \returns
 *      Returns true if all the bits specified in \a msk are set in
 *      \a val, false otherwise.
 */
template <
    typename T_V, typename T_M,
    typename = typename std::enable_if<std::is_integral<T_V>::value>::type,
    typename = typename std::enable_if<std::is_integral<T_M>::value>::type
    >
bool is_bit_set(T_V val, T_M msk)
{
    typename std::remove_volatile<
        typename std::make_unsigned<T_V>::type>::type uval = val;
    typename std::make_unsigned<T_M>::type umsk = msk;
   
    return ((uval & umsk) == umsk);
}

} // namespace hodea

#endif /*!_HODEA_BIT_MANIP_HPP_ */
