// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Timer class based on a timestamp counter.
 *
 * This file provides a timer class and methods based on a free-running
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
 * - timestamp()
 *
 * Ticks is the data type used to represent the counter value. On a
 * 32 bit system it is usually a 32 bit unsigned integer. The bitmask
 * counter_msk gives the bits used for the counter, as not all bits of
 * the Ticks type may be required to hold the  counter value.
 * counter_clk_hz gives the frequency the timestamp counter is clocked
 * with. init() initialize the timestamp counter and deinit() stops it.
 * The method timestamp() returns the actual timer counter value.
 *
 * The member variable counter_msk and counter_clk_hz should be constexpr
 * to allow calculation it compile time. init(), deinit() and timestamp()
 * should be const, not modifying member variables.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_TSC_TIMER_HPP_
#define _HODEA_TSC_TIMER_HPP_

namespace hodea {

/**
 * Class providing timer functions based an timestamp counter.
 */
template <class T_time_base>
class Tsc_timer : public T_time_base {
public:
    using Ticks = typename T_time_base::Ticks;

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
        Ticks now = T_time_base::timestamp();
        return elapsed(ts_start, now) >= period;
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
        Ticks now = T_time_base::timestamp();

        if (elapsed(ts_start, now) >= period) {
            ts_start = now;
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
        Ticks start = T_time_base::timestamp();

        while (!is_elapsed(start, period)) ;
     }

};


} // namespace hodea

#endif /*!_HODEA_TSC_TIMER_HPP_ */
