// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

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
