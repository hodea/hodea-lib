// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * Support for configuring the STM32 device pins.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_STM32_PIN_CONFIG_HPP_
#define _HODEA_STM32_PIN_CONFIG_HPP_

#include <hodea/core/cstdint.hpp>
#include <hodea/core/bitmanip.hpp>
#include <hodea/device/stm32/stm32_device_setup.hpp>

namespace hodea {

/**
 * Enumeration listing the possible alternate function modes.
 */
enum struct Gpio_pin_af : unsigned {
    af0, af1, af2, af3, af4, af5, af6, af7, af8,
    af9, af10, af11, af12, af13, af14, af15
};

/**
 * Class to configure the alternate function of the pins of a port.
 */
class Config_gpio_af {
public:
    Config_gpio_af(GPIO_TypeDef* gpio) : gpio{gpio}, afr{0} {}

    Config_gpio_af& read()
    {
        afr = (static_cast<uint64_t>(gpio->AFR[1]) << 32) | gpio->AFR[0];
        return *this;
    }

    Config_gpio_af& write()
    {
        gpio->AFR[0] = afr & 0xffffffffU;
        gpio->AFR[1] = afr >> 32;
        return *this;
    }

    Config_gpio_af& pin(int pin, Gpio_pin_af af)
    {
        modify_bits(
            afr,
            static_cast<uint64_t>(0xffff) << (4 * pin),
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
