// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Simple countdown timer based on timestamp counter class Tsc.
 *
 * \author f.hollerer@hodea.org
 */
#if !defined HODEA_TSC_TIMER_HPP
#define HODEA_TSC_TIMER_HPP

#include <hodea/core/cstdint.hpp>
#include <hodea/core/math.hpp>
#include <hodea/core/tsc.hpp>

namespace hodea {

/**
 * Class providing a countdown timer base on temstamp counter class.
 */
template <typename T_ticks, class T_tsc>
class Tsc_timer
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
        return math_round_to<Ticks>(T_tsc::counter_clk_hz * sec);
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
        return (static_cast<uint64_t>(us) * T_tsc::counter_clk_hz)
                    / 1000000;
    }

    /**
     * Start countdown timer.
     *
     * \param[in] ticks
     *      Period of time to load the timer with.
     */
    void start(Ticks ticks)
    {
        value = ticks + expired;
        ts_last = T_tsc::now();
    }

    /**
     * Stop countdown timer.
     */
    void stop() { value = stopped; }

    /**
     * Test if timer is expired.
     */
    bool is_expired() { return value == expired; }

    /**
     * Test if timer is stopped.
     */
    bool is_stopped() { return value == stopped; }

    /**
     * Test if timer is running.
     */
    bool is_running() { return value > expired; }

    /**
     * Get ticks remaining till the timer expires.
     */
    Ticks remaining()
    {
        return is_running() ? (value - expired) : 0;
    }

    /**
     * Update timer value.
     *
     * This method uses the timestamp counter to measure the time
     * elapsed since its last invocation and updates the internal timer
     * value accordingly. The time between two invocations must be less
     * than the time duration provided by the underlying timestamp counter
     * minus 2 ticks.
     */
    void update()
    {
        if (is_running()) {
            typename T_tsc::Ticks now = T_tsc::now();
            typename T_tsc::Ticks elapsed;
          
            elapsed = T_tsc::elapsed(ts_last, now);

            if (value > (elapsed + expired))
                value -= elapsed;
            else
                value = expired;

            ts_last = now;
        }
    }

private:
    typename T_tsc::Ticks ts_last;
    Ticks value = stopped;

    static constexpr Ticks stopped = 0;
    static constexpr Ticks expired = 1;
};


} // namespace hodea

#endif /*!HODEA_TSC_TIMER_HPP */
