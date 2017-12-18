// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Hodea time stamp counter.
 *
 * The hodea timestamp counter is an instance of a Tsc_timer class used
 * used within the hodea library as system timer. It can also be used
 * by the user of the hodea library within their own application if the
 * the resolution and maximum time span covered by the timer fits their
 * needs.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined HODEA_RTE_HTSC_HPP
#define HODEA_RTE_HTSC_HPP

#include <hodea/core/tsc.hpp>
#include <hodea/core/tsc_timer.hpp>
#include "hodea_user_config.hpp"
#include HODEA_CONFIG_HTSC_TIME_BASE_INCLUDE

namespace hodea {

using Htsc = Tsc<Htsc_time_base>;
using Htsc_timer = Tsc_timer<uint_fast32_t, Htsc>;

} // namespace hodea

#endif /*!HODEA_RTE_HTSC_HPP */
