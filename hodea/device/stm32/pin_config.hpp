// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * General Purpose I/O pin configuration.
 *
 * This file provides support to configure the GPIOx registers which
 * define the properties of the I/O pins.
 *
 * Device Reset values
 * -------------------
 *
 * On reset all pins except PA13/SYS_SWDIO and PA14/SYS_SWCLK are
 * configured as digital input.  PA13 and PA14 are in AF0 mode.
 *
 * GPIOx_MODER
 *      all pins are digital input, except PA13 and PA14
 * GPIOx_OTYPER
 *      all outputs are in push-pull output mode
 * GPIOx_OSPEEDR
 *      all pins set to low speed, except PA14/SYS_SWCLK for which
 *      high speed is enabled
 *      low speed: up to 2 MHz
 * GPIOx_PUBDR
 *      no pull-up / pull-down, except PA13 and PA14 where pull-up is
 *      enabled
 * GPIOx_ODR
 *      all bits cleared
 * GPIOx_AFRL, GPIOx_AFRH
 *      all pins set to AF0 (active if alternate function mode selected)
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_STM32_PIN_CONFIG_HPP_
#define _HODEA_STM32_PIN_CONFIG_HPP_

#include <hodea/core/cstdint.hpp>
#include <hodea/core/bitmanip.hpp>
#include <hodea/device/stm32/device_setup.hpp>

namespace hodea {

/**
 * Enumeration listing the possible operation modes.
 */
enum struct Gpio_pin_mode {
    input = 0,
    output = 1,
    af = 2,
    analog = 3
};

/**
 * Class to configure a pin's mode.
 *
 * This class is used to initialize or update the GPIOx_MODER register
 * which determines the operation mode of the pins of the port.
 * 
 * The following example sets GPIOB pin 9 and 10 to AF mode, all
 * others are set to 0 which means input mode.
 *
 * \code
 * Config_gpio_mode{GPIOB}
 *      .pin(9, Gpio_pin_mode::af)
 *      .pin(10, Gpio_pin_mode::af)
 *      .write();
 * \endcode
 *
 * To update individual pins while keeping the others unaffected
 * someone can put the read() method in front. The example below sets
 * GPIOB pin 9 and 10 to AF mode without changing the others.
 *
 * \code
 * Config_gpio_mode{GPIOB}
 *      .read()
 *      .pin(9, Gpio_pin_mode::af)
 *      .pin(10, Gpio_pin_mode::af)
 *      .write();
 * \endcode
 */
class Config_gpio_mode {
public:
    Config_gpio_mode(GPIO_TypeDef* gpio) : gpio{gpio}, moder{0} {}

    Config_gpio_mode& read()
    {
        moder = gpio->MODER;
        return *this;
    }

    void write()
    {
        gpio->MODER = moder;
    }

    Config_gpio_mode& pin(int pin, Gpio_pin_mode mode)
    {
        modify_bits(
            moder,
            static_cast<uint32_t>(0x3) << (2 * pin),
            static_cast<uint32_t>(mode) << (2 * pin)
            );
        return *this;
    }

private:
    GPIO_TypeDef* const gpio; 
    uint32_t moder;
};

/**
 * Enumeration listing the possible output types.
 */
enum struct Gpio_pin_otype {
    push_pull = 0,
    open_drain = 1
};

/**
 * Class to configure a pin's output type.
 *
 * This class is used to initialize or update the GPIOx_OTYPER register
 * which determines the output type of the pins of the port.
 * 
 * The following example sets GPIOB pin 9 and 10 to open drain, all
 * others are set to 0 which means push-pull.
 *
 * \code
 * Config_gpio_otype{GPIOB}
 *      .pin(9, Gpio_pin_otype::open_drain)
 *      .pin(10, Gpio_pin_otype::open_drain)
 *      .write();
 * \endcode
 *
 * To update individual pins while keeping the others unaffected
 * someone can put the read() method in front. The example below sets
 * GPIOB pin 9 and 10 to open drain without changing the others.
 *
 * \code
 * Config_gpio_otype{GPIOB}
 *      .read()
 *      .pin(9, Gpio_pin_otype::open_drain)
 *      .pin(10, Gpio_pin_otype::open_drain)
 *      .write();
 * \endcode
 */
class Config_gpio_otype {
public:
    Config_gpio_otype(GPIO_TypeDef* gpio) : gpio{gpio}, otyper{0} {}

    Config_gpio_otype& read()
    {
        otyper = gpio->OTYPER;
        return *this;
    }

    void write()
    {
        gpio->OTYPER = otyper;
    }

    Config_gpio_otype& pin(int pin, Gpio_pin_otype otype)
    {
        modify_bits(otyper, 1U << pin, static_cast<uint16_t>(otype) << pin);
        return *this;
    }

private:
    GPIO_TypeDef* const gpio; 
    uint16_t otyper;
};

/**
 * Enumeration listing the possible output speeds.
 */
enum struct Gpio_pin_ospeed {
    low = 0,
    medium = 1,
    high = 3
};

/**
 * Class to configure a pin's output speed.
 *
 * This class is used to initialize or update the GPIOx_OSPEEDR register
 * which determines the output speed of the pins of the port.
 * 
 * The following example sets GPIOB pin 9 and 10 to high speed, all
 * others are set to 0 which means low speed.
 *
 * \code
 * Config_gpio_ospeed{GPIOB}
 *      .pin(9, Gpio_pin_ospeed::speed)
 *      .pin(10, Gpio_pin_ospeed::speed)
 *      .write();
 * \endcode
 *
 * To update individual pins while keeping the others unaffected
 * someone can put the read() method in front. The example below sets
 * GPIOB pin 9 and 10 to high speed without changing the others.
 *
 * \code
 * Config_gpio_ospeed{GPIOB}
 *      .read()
 *      .pin(9, Gpio_pin_ospeed::speed)
 *      .pin(10, Gpio_pin_ospeed::speed)
 *      .write();
 * \endcode
 */
class Config_gpio_ospeed {
public:
    Config_gpio_ospeed(GPIO_TypeDef* gpio) : gpio{gpio}, ospeedr{0} {}

    Config_gpio_ospeed& read()
    {
        ospeedr = gpio->OSPEEDR;
        return *this;
    }

    void write()
    {
        gpio->OSPEEDR = ospeedr;
    }

    Config_gpio_ospeed& pin(int pin, Gpio_pin_ospeed ospeed)
    {
        modify_bits(
            ospeedr,
            static_cast<uint32_t>(0x3) << (2 * pin),
            static_cast<uint32_t>(ospeed) << (2 * pin)
            );
        return *this;
    }

private:
    GPIO_TypeDef* const gpio; 
    uint32_t ospeedr;
};

/**
 * Enumeration listing the possible pull-up / pull-down configuration.
 */
enum struct Gpio_pin_pupd {
    none = 0,
    pull_up = 1,
    pull_down = 2
};

/**
 * Class to configure a pull-up / pull-down for a pin.
 *
 * This class is used to initialize or update the GPIOx_PUPDR register
 * which determines the pull-up / pull-down configuration for the
 * pins of the port.
 *
 * The following example configures pull-up for GPIOB pin 9 and 10,
 * all others are set to 0 which means no pull-up / pull-down.
 *
 * \code
 * Config_gpio_pupd{GPIOB}
 *      .pin(9, Gpio_pin_pupd::pull_up)
 *      .pin(10, Gpio_pin_pupd::pull_up)
 *      .write();
 * \endcode
 *
 * To update individual pins while keeping the others unaffected
 * someone can put the read() method in front. The example below configures
 * pull-up for GPIOB pin 9 and 10 without changing the others.
 *
 * \code
 * Config_gpio_pupd{GPIOB}
 *      .read()
 *      .pin(9, Gpio_pin_pupd::pull_up)
 *      .pin(10, Gpio_pin_pupd::pull_up)
 *      .write();
 * \endcode
 */
class Config_gpio_pupd {
public:
    Config_gpio_pupd(GPIO_TypeDef* gpio) : gpio{gpio}, pupdr{0} {}

    Config_gpio_pupd& read()
    {
        pupdr = gpio->PUPDR;
        return *this;
    }

    void write()
    {
        gpio->PUPDR = pupdr;
    }

    Config_gpio_pupd& pin(int pin, Gpio_pin_pupd pupd)
    {
        modify_bits(
            pupdr,
            static_cast<uint32_t>(0x3) << (2 * pin),
            static_cast<uint32_t>(pupd) << (2 * pin)
            );
        return *this;
    }

private:
    GPIO_TypeDef* const gpio; 
    uint32_t pupdr;
};

/**
 * Enumeration listing the possible alternate functions.
 */
enum struct Gpio_pin_af {
    af0 = 0,
    af1, af2, af3, af4, af5, af6, af7, af8,
    af9, af10, af11, af12, af13, af14, af15
};

/**
 * Class to configure a pin's alternate function.
 *
 * This class is used to initialize or update the GPIOx_AFRL and GPIOx_AFRH
 * registers which determine the alternate function of the pins of the
 * port.
 * 
 * The reset value of these registers is 0, which means AF0.
 *
 * The following example sets GPIOB pin 9 to AF2 and pin 10 to AF4. All
 * others are set to their reset value 0.
 *
 * \code
 * Config_gpio_af{GPIOB}
 *      .pin(9, Gpio_pin_af::af2)
 *      .pin(10, Gpio_pin_af::af4)
 *      .write();
 * \endcode
 *
 * To update individual pins while keeping the others unaffected
 * someone can put the read() method in front. The example below sets
 * GPIOB pin 9 to AF2 and pin 10 to AF4 without changing the others.
 *
 * \code
 * Config_gpio_af{GPIOB}
 *      .read()
 *      .pin(9, Gpio_pin_af::af2)
 *      .pin(10, Gpio_pin_af::af4)
 *      .write();
 * \endcode
 */
class Config_gpio_af {
public:
    Config_gpio_af(GPIO_TypeDef* gpio) : gpio{gpio}, afr{0} {}

    Config_gpio_af& read()
    {
        afr = (static_cast<uint64_t>(gpio->AFR[1]) << 32) | gpio->AFR[0];
        return *this;
    }

    void write()
    {
        gpio->AFR[0] = afr & 0xffffffffU;
        gpio->AFR[1] = afr >> 32;
    }

    Config_gpio_af& pin(int pin, Gpio_pin_af af)
    {
        modify_bits(
            afr,
            static_cast<uint64_t>(0xf) << (4 * pin),
            static_cast<uint64_t>(af) << (4 * pin)
            );
        return *this;
    }

private:
    GPIO_TypeDef* const gpio; 
    uint64_t afr;
};

} // namespace hodea

#endif /*!_HODEA_STM32_PIN_CONFIG_HPP_ */
