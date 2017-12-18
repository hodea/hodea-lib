// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Timing methods based on a timestamp counter.
 *
 * This file provides timing methods based on a free-running timestamp
 * counter. The counter is used as time base. Having two counter values,
 * e.g. the counter value from the start point and the actual counter
 * value, the difference of this two counter values gives the time elapsed
 * since the start point. With this information we can measure the
 * execution time, provide delay functions or test if a given period has
 * elapsed.
 *
 * The idea of the timestamp counter is derived from the Linux kernel
 * which uses a global tick "jiffies" and several macros to check if a
 * given period of time has passed.
 *
 * According Wikipedia jiffy is an informal term for any unspecific short
 * period of time, as in "I'll be back in a jiffy".
 *
 * The counter used as time base must be provided by the user via a
 * time class. The class can either use a hardware timer or software
 * counter to provide the counter information. The class must provide
 * the following public methods and member variables.
 *
 * - Ticks
 * - counter_msk
 * - counter_clk_hz
 * - init()
 * - deinit()
 * - now()
 *
 * Ticks is the data type used to represent the counter value. On a
 * 32 bit system it is usually a 32 bit unsigned integer. The bitmask
 * counter_msk gives the bits used for the counter, as not all bits of
 * the Ticks type may be required to hold the  counter value.
 * counter_clk_hz gives the frequency the timestamp counter is clocked
 * with. init() initialize the timestamp counter and deinit() stops it.
 * The method now() returns the timestamp of the actual time, with is the
 * current timer counter value.
 *
 * The member variable counter_msk and counter_clk_hz should be constexpr
 * to allow calculation it compile time. init(), deinit() and timestamp()
 * should be const, not modifying member variables.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined HODEA_TSC_HPP
#define HODEA_TSC_HPP

#include <hodea/core/cstdint.hpp>
#include <hodea/core/math.hpp>

namespace hodea {

/**
 * Class providing timing methods based on a timestamp counter.
 */
template <class T_time_base>
class Tsc : public T_time_base {
public:
    using Ticks = typename T_time_base::Ticks;

    /**
     * Convert seconds into ticks at compile time [compile time].
     *
     * This method converts seconds into ticks. Its preferred use is at
     * compile time. If you need to perform the calculation at runtime
     * consider to use \a i_us_to_ticks() instead.
     */
    static constexpr Ticks sec_to_ticks(double sec)
    {
        return math_round_to<Ticks>(T_time_base::counter_clk_hz * sec);
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
        return (static_cast<uint64_t>(us) * T_time_base::counter_clk_hz)
                    / 1000000;
    }

    /**
     * Give the time elapsed between to timestamps.
     *
     * \param[in] ts_older
     *      The timestamp which is the older one of the two timestamps.
     * \param[in] ts_newer
     *      The timestamp which is the newer one of the two timestamps.
     */
    static Ticks elapsed(Ticks ts_older, Ticks ts_newer)
    {
        return (ts_newer - ts_older) & T_time_base::counter_msk;
    }

    /**
     * Test if a given period of time is elapsed.
     *
     * \param[in] ts_start
     *      Timestamp of the starting time.
     * \param[in] period
     *      Time period to test whether it is elapsed or not.
     *
     * \returns
     *      True if the given period is elapsed, false otherwise.
     */
    static bool is_elapsed(Ticks ts_start, Ticks period)
    {
        return elapsed(ts_start, T_time_base::now()) >= period;
    }

    /**
     * Test period and update start timestamp to provide repetitive timer.
     *
     * This method tests if a given period is elapsed, and moves the
     * start timestamp to the actual time in this case to provide a
     * repetitive timer.
     *
     * \param[in,out] ts_start
     *      Timestamp of the starting time.
     * \param[in] period
     *      Time period to test whether it is elapsed or not.
     *
     * \returns
     *      True if the given period is elapsed, false otherwise.
     */
    static bool is_elapsed_repetitive(Ticks& ts_start, Ticks period)
    {
        Ticks ts_now = T_time_base::now();

        if (elapsed(ts_start, ts_now) >= period) {
            ts_start = ts_now;
            return true;
        }
        return false;
    }

    /**
     * Delay execution for a certain number of ticks.
     *
     * \param[in] period
     *      The number of ticks to delay the execution.
     */
    static void delay(Ticks period)
    {
       Ticks start = T_time_base::now();

        while (!is_elapsed(start, period)) ;
     }
};


} // namespace hodea

#endif /*!HODEA_TSC_HPP */
