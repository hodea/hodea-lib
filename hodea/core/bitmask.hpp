// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Functions to create bitmasks, preferable at compile time.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_BITMASK_HPP_
#define _HODEA_BITMASK_HPP_

#include <type_traits>

namespace hodea {
namespace helper {

/**
 * Class to construct a right aligned bitmask at compile time.
 *
 * This is a helper class for \a bitmask(). It is used to construct
 * a right aligned bitmask according the number of bits the bitmask covers
 * at compile time by using template recursion.
 *
 * \note
 * We use template recursion instead of a recursive constexpr function
 * to enforce that the mask is created at compile time.
 */
template <class T, int number_of_bits>
class Right_aligned_mask {
public:
    constexpr Right_aligned_mask() :
        msk {(static_cast<T>(1) << (number_of_bits - 1)) |
                Right_aligned_mask<T, number_of_bits - 1>{}}
    {}

    constexpr operator T() const {return msk;}

private:
    T msk;
};

/**
 * Class Right_align_mask specialization to end recursion.
 */
template <class T>
struct Right_aligned_mask<T, 0> {
public:
    constexpr Right_aligned_mask() {}

    constexpr operator T() const {return 0;}
};

} // namespace hodea::helper

/**
 * Construct a bitmask based on its position and its length.
 */
template <
    typename T, int pos, int number_of_bits = 1,
    typename = typename std::enable_if<std::is_unsigned<T>::value>::type
    >
constexpr T bitmask()
{
    return helper::Right_aligned_mask<T, number_of_bits>{} << pos;
}

} // namespace hodea

#endif /*!_HODEA_BITMASK_HPP_ */
