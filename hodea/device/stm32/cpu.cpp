// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * CPU related functions for STM32 devices.
 *
 * \author f.hollerer@gmx.net
 */
#include <hodea/device/hal/cpu.hpp>

namespace hodea {

constexpr unsigned iwdg_clock_hz = 40000; 

/**
 * Set watchdog period.
 *
 * \param[in] period Watchdog period in [ms].
 */
void set_watchdog_period(int period)
{
    unsigned reload;
    unsigned prescaler;

    reload = (iwdg_clock_hz / (4 * 1000)) * period; 

    // find required prescaler
    prescaler = 0;
    while (reload > IWDG_RLR_RL) {
        prescaler++;
        reload >>= 1;
    }
    if (prescaler >= IWDG_PR_PR) {
        reload = IWDG_RLR_RL;
        prescaler = IWDG_PR_PR - 1;
    }

    IWDG->KR = 0x5555;      // unlock

    IWDG->PR = prescaler;
    IWDG->RLR = reload;

    /*
     * Wait till reload and period value are updated.
     * Takes maximum 5 cycles @ iwdg_clock_hz.
     */
    while (is_bit_set(IWDG->SR, IWDG_SR_PVU | IWDG_SR_RVU))
        ;

    IWDG->KR = 0xaaaa;      // kick watchdog to re-lock its registers
}

} // namespace hodea

