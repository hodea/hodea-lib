// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Hodea runtime environment setup.
 *
 * \author f.hollerer@gmx.net
 */

#include <hodea/rte/htsc.hpp>
#include <hodea/rte/setup.hpp>

namespace hodea {

/**
 * Initialize the runtime environment.
 */
void rte_init()
{
    Htsc::init();
}

/**
 * Shutdown of the runtime environment.
 */
void rte_deinit()
{
    Htsc::deinit();
}

} // namespace hodea

