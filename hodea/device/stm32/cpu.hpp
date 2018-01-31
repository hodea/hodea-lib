// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * CPU related functions for STM32 devices.
 *
 * \author f.hollerer@hodea.org
 */
#if !defined HODEA_STM32_CPU_HPP
#define HODEA_STM32_CPU_HPP

#include <hodea/core/cstdint.hpp>
#include <hodea/core/bitmanip.hpp>
#include <hodea/device/hal/device_setup.hpp>

namespace hodea {

/**
 * Bitmasks determining the reset cause.
 *
 * The following enumeration lists different reset causes.
 *
 * Reset causes can be ORed together to indicated that different
 * resets occurred since cleared with \a clear_reset_causes().
 *
 * The reset pin is bidirectional. With a software reset the MCU drives
 * this pin to low to reset the external circuit. Therefore, a software
 * reset causes Reset_cause::software _AND_ Reset_cause::reset_pin to
 * be set.
 *
 * \note
 * POR and PDR use the same reset flag on ST devices. Therefore,
 * we cannot distinguish between power-on reset and brownout on this
 * platform.
 */
class Reset_cause {
public:
    typedef uint32_t Type;              // underlying enumeration type

    enum : Type {
        power_on = RCC_CSR_PORRSTF,
        reset_pin = RCC_CSR_PINRSTF,
        software = RCC_CSR_SFTRSTF,

#if defined RCC_CSR_V18PWRRSTF
        v18pwr = RCC_CSR_V18PWRRSTF,    // V1.8 power domain reset
#endif

        obl = RCC_CSR_OBLRSTF,          // option byte load reset
        iwdg = RCC_CSR_IWDGRSTF,        // independent watchdog reset
        wwgdg = RCC_CSR_WWDGRSTF,       // window watchdog reset
        lpwr = RCC_CSR_LPWRRSTF,        // low-power reset

        all_flags =
            power_on | reset_pin | software | obl | iwdg | wwgdg | lpwr
#if defined RCC_CSR_V18PWRRSTF
            |v18pwr
#endif
    };
};

/**
 * No operation.
 */
static inline void nop()
{
    __NOP();
}

/**
 * Software reset.
 *
 * Restart the system via software reset. This is guaranteed to never
 * return.
 */
[[noreturn]] static inline void software_reset()
{
    NVIC_SystemReset();

    for (;;) ;  // avoid warning as NVIC_SystemReset() misses [[noreturn]]
}

/**
 * Get the reset cause(s).
 *
 * \returns
 *      Bitmask defining the reset cause or causes occurred since cleared.
 */
static inline Reset_cause::Type get_reset_cause()
{
    return RCC->CSR & Reset_cause::all_flags;
}

/**
 * Clear all reset causes.
 */
static inline void clear_reset_causes()
{
    hodea::set_bit(RCC->CSR, RCC_CSR_RMVF);
}

/**
 * Set watchdog period.
 *
 * \param[in] period Watchdog period in [ms].
 */
void set_watchdog_period(int period);

/**
 * Enable watchdog with setting its period.
 *
 * If the option byte USER bit WDG_SW is set (1: software watchdog),
 * the independent watchdog (IWDG) is disabled after reset and must be
 * enabled by software.
 * If WDG_SW is cleared (0: hardware watchdog) the watchdog is immediately
 * enabled after reset.
 *
 * The reset configuration for the watchdog timer period when using
 * the hardware watchdog option is 409.6 ms.
 *
 * It is not possible to deactivate the watchdog once enabled.
 *
 * \param[in] period
 *      Watchdog period in [ms]. If 0, the actual period is not changed.
 */
static inline void enable_watchdog(int period = 0)
{
    IWDG->KR = 0xcccc;
    if (period)
        set_watchdog_period(period);
}

/**
 * Kick the watchdog.
 *
 * This function services the independent watchdog (IWDG).
 *
 * The watchdog must be enabled via option byte USER, bit WDG_SW cleared
 * or bey a call to \a enable_watchdog().
 */
static inline void kick_watchdog()
{
    IWDG->KR = 0xaaaa;
}

} // namespace hodea

#endif /*!HODEA_STM32_CPU_HPP */
