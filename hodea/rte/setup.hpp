// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Hodea runtime environment setup.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_RTE_SETUP_HPP_
#define _HODEA_RTE_SETUP_HPP_

namespace hodea {

/**
 * Initialize the runtime environment.
 */
void rte_init();

/**
 * Shutdown of the runtime environment.
 */
void rte_deinit();

} // namespace hodea

#endif /*!_HODEA_RTE_SETUP_HPP_ */
