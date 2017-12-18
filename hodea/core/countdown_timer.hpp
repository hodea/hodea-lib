// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Simple countdown timer based on Tsc_timer.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined HODEA_COUNTDOWN_TIMER_HPP
#define HODEA_COUNTDOWN_TIMER_HPP

#include <hodea/core/cstdint.hpp>
#include <hodea/core/math.hpp>
#include <hodea/core/tsc_timer.hpp>

namespace hodea {

/**
 * Class providing a countdown timer.
 */
template <typename T_ticks, class T_tsc_timer>
class Countdown_timer
{
public:
    typedef T_ticks Ticks;

    /**
     * Convert seconds into ticks at compile time [compile time].
     *
     * This method converts seconds into ticks. Its preferred use is at
     * compile time. If you need to perform the calculation at runtime
     * consider to use \a i_us_to_ticks() instead.
     */
    static constexpr Ticks sec_to_ticks(double sec)
    {
        return math_round_to<Ticks>(T_tsc_timer::counter_clk_hz * sec);
    }

    /**
     * Convert milliseconds into ticks at compile time [compile time].
     *
     * This method converts milliseconds into ticks. Its preferred use is
     * at compile time. If you need to perform the calculation at runtime
     * consider to use \a i_us_to_ticks() instead.
     */
    static constexpr Ticks ms_to_ticks(double ms)
    {
        return sec_to_ticks(ms * 1e-3);
    }

    /**
     * Convert microseconds into ticks at compile time [compile time].
     *
     * This method converts microseconds into ticks. Its preferred use is
     * at compile time. If you need to perform the calculation at runtime
     * consider to use \a i_us_to_ticks() instead.
     */
    static constexpr Ticks us_to_ticks(double us)
    {
        return sec_to_ticks(us * 1e-6);
    }

    /**
     * Convert microseconds into ticks using integer arithmetic [runtime].
     *
     * This method converts microseconds into ticks using integer
     * arithmetic. Its preferred use is at runtime, but can also be
     * used at compile time.
     * In contrast to the implementations using floating point operations,
     * this method does not apply rounding.
     */
    static constexpr Ticks i_us_to_ticks(unsigned us)
    {
        return (static_cast<uint64_t>(us) * T_tsc_timer::counter_clk_hz)
                    / 1000000;
    }


private:
    typename T_tsc_timer::Ticks ts_last;
    uint_fast32_t value;

    static constexpr uint_fast32_t stopped_value = 0;
    static constexpr uint_fast32_t expired_value = 1;
};


} // namespace hodea

#endif /*!HODEA_COUNTDOWN_TIMER_HPP */
