// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Support for digital inputs and outputs.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_IMX_M4_DIGIO_HPP_
#define _HODEA_IMX_M4_DIGIO_HPP_

#include <hodea/core/cstdint.hpp>
#include <hodea/core/bitmanip.hpp>
#include <hodea/device/hal/critical_section.hpp>
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
 *
 * This class is used to name a digital I/O pin. E.g. the following line
 * defines a constant which can be used to refer to the debug pin:
 *
 * \code static const Digio_pin(GPIO2_BASE, 12) debug_pin; \endcode
 *
 * Please note that we pass the base address of the port as uintptr_t to
 * the constructor, instead of using the peripheral pointer. This allows
 * the compiler to treat the parameter as constant and perform adequate
 * optimizations. Tests with gcc showed that the compiler does not need to
 * instantiate debug_pin in this case. It can inline the code. The
 * resulting code is equivalent in terms of code size and runtime to the C
 * macros and inline functions we used in the past.
 *
 * The compiler cannot achieve this if we pass the gpio port via its
 * peripheral pointer. A class which supports the definition below would
 * cause footprint and performance penalties.
 *
 * \code static const Digio_pin(GPIO2, 12) debug_pin; // penalties!!
 * \endcode
 *
 * Fortunately, the CMSIS standard requires the chip vendors to define
 * both. The address constant and the peripheral pointer.  \see
 * http://arm-software.github.io/CMSIS_5/Core/html/device_h_pg.html
 */
class Digio_pin {
public:
    constexpr Digio_pin(uintptr_t port_base, int pin)
        : port_base(port_base), _pin(pin)
    { }

    constexpr int pin() const {return _pin;}

    constexpr uint32_t mask() const {return 1U << _pin;}

    GPIO_Type* const port() const
    {
        return reinterpret_cast<GPIO_Type*>(port_base);
    }

private:
    const uintptr_t port_base;
    const int _pin;
};

/**
 * Class to control a digital output.
 *
 * Special care must be taken on the i.MX when operating with digital
 * outputs. In contrast to many other controllers from serious chip
 * vendors, the i.MX does not have separate bits to set and reset an
 * output. Setting or resetting a single pin of a port requires a
 * read-modify-write cycle, which is subject to race conditions.
 *
 * We assume that a digital I/O port is either exclusively assigned
 * to the Cortex-A7 core(s), or to the Cortex-M4 core. We use a
 * critical section to protect modifications of an I/O port on the
 * M4 side. For non-exclusive use of an I/O port the user must
 * implement additional locking within the application to prevent
 * race conditions across the cores.
 */
class Digio_output : public Digio_pin {
public:
    constexpr Digio_output(uintptr_t port_base, int pin)
        : Digio_pin(port_base, pin) {}

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
     *
     * \note
     * Reading the actual output value is not supported by this
     * controller. The i.MX7 does not support open-drain outputs
     * at all.
     */
    Digio_pin_value value() const
    {
        return (port()->DR >> pin()) & 1;
    }

    /**
     * Set digital output to the given value.
     *
     * \param[in] val
     *      0, false: reset output pin
     *      1, true: set output pin
     */
    Digio_pin_value value(Digio_pin_value val) const
    {
        val ? set() : reset();
    }

    /// Set digital output to low.
    void reset() const
    {
        Critical_section cs;

        cs.lock();
        hodea::clr_bit(port()->DR, mask());
        cs.unlock();
    }

    /// Set digital output to high.
    void set() const
    {
        Critical_section cs;

        cs.lock();
        hodea::set_bit(port()->DR, mask());
        cs.unlock();
    }

    /// Toggle digital output.
    void toggle() const
    {
        Critical_section cs;
        cs.lock();
        hodea::toggle_bit(port()->DR, mask());
        cs.unlock();
    }
};

/**
 * Class to control a digital input.
 */
class Digio_input : public Digio_pin {
public:
    constexpr Digio_input(uintptr_t port_base, int pin)
        : Digio_pin(port_base, pin) {}

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
        return (port()->PSR >> pin()) & 1;
    }
};

/**
 * Configure selected pins of a GPIO port.
 *
 * This function disables the interrupt, resets the edge selection
 * and configures the direction for the given pins of a port.
 *
 * \param[in,out] port
 *      The GPIO port to which to apply the configuration.
 * \param[in] input_pins
 *      Bitmask selecting the pins to configure as input.
 * \param[in] output_pins
 *      Bitmask selecting the pins to configure as output.
 *
 * \note
 * Pins not selected with the input_pins and output_pins mask
 * keep unchanged.
 */
static inline void digio_config_pins(
    GPIO_Type* port, uint32_t input_pins, uint32_t output_pins
    )
{
    Critical_section cs;

    uint32_t affected_pins = input_pins | output_pins;

    cs.lock();
    hodea::clr_bit(port->IMR, affected_pins);
    hodea::clr_bit(port->EDGE_SEL, affected_pins);
    hodea::modify_bits(port->GDIR, input_pins, output_pins);
    cs.unlock();
}

/**
 * Modify several outputs of a port simultaneously.
 *
 * \param[in] gpio
 *      The port with the outputs to modify.
 * \param[in] reset_msk
 *      Bitmask selecting the outputs to reset.
 * \param[in] set_msk
 *      Bitmask selecting the outputs to set.
 *
 * Pins not selected with \a reset_msk or \a set_msk are not changed.
 */
static inline void digio_modify_outputs(
    GPIO_Type* gpio, unsigned reset_msk, unsigned set_msk
    )
{
    Critical_section cs;
    cs.lock();
    hodea::modify_bits(gpio->DR, reset_msk, set_msk);
    cs.unlock();
}

} // namespace hodea

#endif /*!_HODEA_IMX_M4_DIGIO_HPP_ */
