// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

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
#if !defined _HODEA_RTE_HTSC_HPP_
#define _HODEA_RTE_HTSC_HPP_

#include <hodea/core/tsc_timer.hpp>
#include "hodea_user_config.hpp"
#include HODEA_CONFIG_HTSC_TIME_BASE_INCLUDE

namespace hodea {

using htsc = Tsc_timer<Htsc_time_base>;

} // namespace hodea

#endif /*!_HODEA_RTE_HTSC_HPP_ */
