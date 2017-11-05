// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Enter and exit critical sections.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_ARM_CM_CRITICAL_SECTION_HPP_
#define _HODEA_ARM_CM_CRITICAL_SECTION_HPP_

#include <atomic>
#include <hodea/core/cstdint.hpp>
#include <hodea/device/hal/device_setup.hpp>

namespace hodea {

/**
 * Class to protect a critical section by disabling the global interrupt.
 *
 * This class can be used to protect operations within a critical section
 * by disabling the global interrupt when entering the section, and
 * restoring the original interrupt enable state when leaving it.
 *
 * The method lock() is provided for entering, unlock() for leaving the
 * section.
 *
 * The class can be used together with a std::lock_guard() or
 * std:unique_lock().
 *
 * We use std::atomic_signal_fence() to ensure that the compiler has
 * finished all load and stores when entering the critical section, and
 * as well when leaving it.
 *
 * \note
 * std::atomic_signal_fence() has the effect of a compiler barrier. The
 * more restrictive std::thread_fence() can be used to apply a full
 * memory barrier.
 * On Cortex-Mx devices a full memory barrier is only required in very
 * special cases, e.g. after relocating the vector table. Therefore, it
 * is save to use the less restrictive compiler barrier here.
 */
class Critical_section {
public:
    void lock()
    {
       primask = __get_PRIMASK();
        __disable_irq();
        std::atomic_signal_fence(std::memory_order_seq_cst);
    }

    void unlock()
    {
        std::atomic_signal_fence(std::memory_order_seq_cst);
        __set_PRIMASK(primask);
    }

private:
    uint32_t primask;
};

} // namespace hodea

#endif /*!_HODEA_ARM_CM_CRITICAL_SECTION_HPP_ */
