// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Functions to create bitmasks, preferable at compile time.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_BIT_mANIP_HPP_
#define _HODEA_BIT_mANIP_HPP_

#include <type_traits>

namespace hodea {

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
 * Create a bitmask at compile time.
 * 
 * \note
 * The parameter are passed s template parameter to ensure that it is
 * resolved at compile time.
 */
template <
    typename T,
    int pos,
    int size = 1
    >
constexpr T make_bitmask()
{
    return 
        (static_cast<T>(1) << (pos + size)) | 
            (size > 1) ? make_bitmask<T, pos, size - 1>() : 0;
}

} // namespace hodea

#endif /*!_HODEA_BIT_mANIP_HPP_ */
