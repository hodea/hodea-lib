// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * ARM systick timer as timebase for htsc.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_ARM_CM_HTSC_SYSTICK_TIME_BASE_HPP_
#define _HODEA_ARM_CM_HTSC_SYSTICK_TIME_BASE_HPP_

#include <hodea/device/hal/device_setup.hpp>

namespace hodea {

/**
 * Timebase of the hodea timestamp counter derived from the SysTick timer.
 */
class Htsc_time_base {
public:
    typedef unsigned Ticks;

    static constexpr Ticks counter_msk = SysTick_VAL_CURRENT_Msk;
    static constexpr unsigned counter_clk_hz = config_systick_hz;

    static void init()
    {
        unsigned clksrc = (config_systick_hz == config_sysclk_hz) ? 1 : 0;
       
        SysTick->VAL = 0;
        SysTick->LOAD = counter_msk;
        SysTick->CTRL =
            _VAL2FLD(SysTick_CTRL_CLKSOURCE, clksrc) |
            _VAL2FLD(SysTick_CTRL_ENABLE, 1);

    }

    static void deinit()
    {
        SysTick->CTRL = 0;
    }

    static Ticks now()
    {
        Ticks ts_now = SysTick->VAL;

        /*
         * The systick timer is a down counter, but we have to return
         * an up-counting timestamp.
         */
        return counter_msk - ts_now;
    }
};


} // namespace hodea

#endif /*!_HODEA_ARM_CM_HTSC_SYSTICK_TIME_BASE_HPP_ */
