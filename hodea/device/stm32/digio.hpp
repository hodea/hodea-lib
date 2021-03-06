// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Digital input / output.
 *
 * \author f.hollerer@hodea.org
 */
#if !defined HODEA_STM32_DIGIO_HPP
#define HODEA_STM32_DIGIO_HPP

#include <hodea/core/cstdint.hpp>
#include <hodea/core/bitmanip.hpp>
#include <hodea/device/hal/device_setup.hpp>

namespace hodea {

/**
 * Type to represent an input or output pin value.
 *
 * The value of an input or output can either be 0 / low or 1 / high.
 *
 * We use bool as underlying type to represent this, as it provides
 * reasonable implicit conversion from bool to int and vice versa:
 *
 * - int --> bool: 0 is converted to false, value different from 0 to true
 * - bool --> int: false is converted to 0, true is converted to 1
 */
typedef bool Digio_pin_value;


 /**
 * Class to name a digital I/O pin.
 */
class Digio_pin {
public:
    constexpr Digio_pin(uintptr_t port_base, int pin)
        : device{port_base}, pin{pin}, msk{1U << pin}
    {}

    const Device_pointer<GPIO_TypeDef> device;
    const int pin;
    const uint32_t msk;
};

/**
 * Class to control a digital output.
 */
class Digio_output : public Digio_pin {
public:
    constexpr Digio_output(uintptr_t port, int pin)
        : Digio_pin(port, pin) {}

    /**
     * Get desired output value.
     *
     * This method returns the desired value of the output. This may
     * be different from the real pin value.
     *
     * Use case is an open collector output with several outputs driving
     * a single line.
     *
     * Consider that the software sets the output value to high, but an
     * external circuit drives the pin low. In this case the desired value
     * for this output is high, while the real value of the pin is low.
     *
     * The desired value is the value set with value(Digio_pin_value val).
     * The initial desired value after a reset is 0.
     *
     * \returns
     *      Desired state of the output pin.
     * \retval 0 output should be low
     * \retval 1 output should be high
     */
    Digio_pin_value value() const
    {
        return (device->ODR >> pin) & 1;
    }

    /**
     * Get the real value of the output pin.
     *
     * This method returns the real pin value of the output. This may
     * be different from the desired value.
     *
     * Use case is an open collector output with several outputs driving
     * a single line.
     *
     * Consider that the software sets the output value to high, but an
     * external circuit drives the pin low. In this case the desired value
     * for this output is high, while the real value of the pin is low.
     *
     * The desired value is the value set with value(Digio_pin_value val).
     * The initial desired value after a reset is 0.
     *
     * \returns
     *      Real state of the output pin.
     * \retval 0 output pin is low
     * \retval 1 output pin is high
     */
    Digio_pin_value real_pin_value() const
    {
        return (device->IDR >> pin) & 1;
    }

    /**
     * Set digital output to the given value.
     *
     * \param[in] val
     *      0, false: reset output pin
     *      1, true: set output pin
     */
    void value(Digio_pin_value val) const
    {
        val ? set() : reset();
    }

    /**
     * Set output to low.
     */
    void reset() const
    {
        device->BRR = msk;
    }

    /**
     * Set output to high.
     */
    void set() const
    {
        device->BSRR = msk;
    }

    /**
     * Toggle digital output pin.
     */
    void toggle() const
    {
        value(!value());
    }
};


/**
 * Class to control a digital input.
 */
class Digio_input : public Digio_pin {
public:
    constexpr Digio_input(uintptr_t port, int pin)
        : Digio_pin(port, pin) {}

    /**
     * Get value of input pin.
     *
     * \returns
     *      State of the input pin.
     * \retval 0 input is low
     * \retval 1 input is high
     */
    Digio_pin_value value() const
    {
        return (device->IDR >> pin) & 1;
    }
};

/**
 * Set output value for several outputs of a port simultaneously.
 *
 * \param[in] port
 *      The gpio port with the outputs to modify.
 * \param[in] reset_msk
 *      Bitmask selecting the outputs to reset.
 * \param[in] set_msk
 *      Bitmask selecting the outputs to set.
 *
 * Pins not selected with \a reset_msk or \a set_msk are not changed.
 */
static inline void digio_modify_outputs(
    GPIO_TypeDef* port, unsigned reset_msk, unsigned set_msk
    )
{
    port->BSRR = (reset_msk << 16) | set_msk;
}

} // namespace hodea

#endif /*!HODEA_STM32_DIGIO_HPP */
