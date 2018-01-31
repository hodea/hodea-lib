// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Hodea runtime environment setup.
 *
 * \author f.hollerer@hodea.org
 */
#if !defined HODEA_RTE_SETUP_HPP
#define HODEA_RTE_SETUP_HPP

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

#endif /*!HODEA_RTE_SETUP_HPP */
