# hodea-lib
Highly Optimized Deeply Embedded Auxiliaries Library

[logo](logo/hodea_logo.png)

---

## About the library

This is a C++ source code library. The term **source code libary** was
chosen to express that it has the character of a library, but is
included as source code to the project and compiled and linked together
with user code. This allows the library to be optimized at compile
time for the respective application.

It provides the basic infrastructure, algorithm and data structures,
utilities and other stuff required for deeply embedded systems. It is
intended for bare metal embedded software, but can also be used as
addition to a real-time operating system (RTOS).

The focus is on small 32 bit microcontroller units (MCUs). Currently,
only ARM Cortex-M based MCUs as the
[STM32F0](http://www.st.com/content/st_com/en/products/microcontrollers/stm32-32-bit-arm-cortex-mcus/stm32-mainstream-mcus/stm32f0-series.html?querycriteria=productId=SS1574)
and the
[STM32F3](http://www.st.com/content/st_com/en/products/microcontrollers/stm32-32-bit-arm-cortex-mcus/stm32-mainstream-mcus/stm32f3-series.html?querycriteria=productId=SS1576)
family are supported.

The library supports:

- Moderate hardware abstraction
- Pin configuration
- Digital input / output
- Bit manipulation
- Serialization
- Little / Big Endian conversion
- Timers based on a free-running hardware timer
- Mathematical functions, e.g. rounding at compile time

In future we will add modules for:

- debouncing
- checksums
- non-locking queues
- etc.

## Design goals

The intended field of used is hard real-time, particularly digital control.
The design of the library is influenced by the authors former engagement
in the development of power supply units (PSU). Key concerns in this field
are:

- The MCU must be cheap. Every cent matters.
- Disabling the global interrupt to protect critical sections is prohibited.
  This would cause jitters to the control loop which in turn might
  damage the hardware.

With that in mind the design goals for this library are:

- Provide support for bare metal software
- Good abstraction, without compromising code size and performance
- Code size and efficiency is essential
- Prefer evaluation at compile time rather than at runtime
- Some code is deliberately in header files to allow evaluation at
  compile time
- Prefer non-locking operations

## Demo project

The
[hodea-stm32f0-project-template](https://github.com/hodea/hodea-stm32f0-project-template)
can serve as starting point for own projects using this library.

