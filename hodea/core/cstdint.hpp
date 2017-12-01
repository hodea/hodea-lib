// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Bring types known from C99 stdint.h into global namespace.
 *
 * C++98 introduced <c*> headers for the standard header files known form
 * C to avoid polluting the global namespace.
 *
 * C++ 11 standard introduces cstdint and marked stdint.h as deprecated.
 *
 * However, implementations persisted in putting the symbols into the
 * global namespace anyway, and C++11 ratified this practice.
 * 
 * Thus cstdint shipped with the compiler may or may not put the
 * types known from stdint.h into the global namespace.
 *
 * As we often need this types in embedded system, this wrapper include
 * file makes sure that types are in the global namespace.
 *
 * Details \see
 * https://stackoverflow.com/questions/13642827/cstdint-vs-stdint-h
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_CSTDINT_HPP_
#define _HODEA_CSTDINT_HPP_

#include <cstdint>

namespace std
{
    using ::int8_t;
    using ::int16_t;
    using ::int32_t;
    using ::int64_t;

    using ::int_fast8_t;
    using ::int_fast16_t;
    using ::int_fast32_t;
    using ::int_fast64_t;

    using ::int_least8_t;
    using ::int_least16_t;
    using ::int_least32_t;
    using ::int_least64_t;

    using ::intmax_t;
    using ::intptr_t;
    
    using ::uint8_t;
    using ::uint16_t;
    using ::uint32_t;
    using ::uint64_t;

    using ::uint_fast8_t;
    using ::uint_fast16_t;
    using ::uint_fast32_t;
    using ::uint_fast64_t;

    using ::uint_least8_t;
    using ::uint_least16_t;
    using ::uint_least32_t;
    using ::uint_least64_t;

    using ::uintmax_t;
    using ::uintptr_t;
} // namespace std


#endif /*!_HODEA_CSTDINT_HPP_ */
