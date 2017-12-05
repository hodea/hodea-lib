// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * IOMUX - I/O multiplexer pin configuration support.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined HODEA_IMX7_M4_PIN_CONFIG_HPP
#define HODEA_IMX7_M4_PIN_CONFIG_HPP

#include <hodea/device/hal/device_setup.hpp>

namespace hodea {

/**
 * Enumeration listing possible values for the PAD pull select field.
 */
enum struct Pad_ps {
    pd100k = 0,
    pu5k = 1,
    pu47k = 2,
    pu100k = 3
};

/**
 * Enumeration listing possible values for the PAD driver strength field.
 *
 * \note
 * Within the reference manual the field is named 'dse'. It is not obvious
 * why NXP name it this way, but we stick with this name to avoid
 * confusion.
 */
enum struct Pad_dse {
    x1 = 0,
    x2 = 2,
    x3 = 1,
    x6 = 3
};

/**
 * \brief Configure IOMUX MUX_CTL and PAD_CTL for the given pad.
 *
 * \param[in] pad
 *      The pad name.
 * \param[in] mux_mode
 *      MUX mode select.
 * \param[in] ps
 *      Pull up/down select; 0: 100K PD, 1: 5K PU, 2: 47K PU, 3: 100K PU
 * \param[in] pe
 *      Pull enable.
 * \param[in] hys
 *      Hysteresis enable; 0: disabled, 1: enabled
 * \param[in] sre
 *      Slew rate; 0: fast slew rate, 1: slow slow rate
 * \param[in] dse
 *      Drive strength; 0: X1, 1: X4, 2: X2, 3: X6
 */
#define iomux_config_pad(pad, mux_mode, ps, pe, hys, sre, dse)          \
    do {                                                                \
        IOMUXC->SW_MUX_CTL_PAD_ ## pad = (mux_mode);                    \
        IOMUXC->SW_PAD_CTL_PAD_ ## pad =                                \
            _NXP_VAL2FLD(                                               \
                IOMUXC_SW_PAD_CTL_PAD_ ## pad ## _PS,                   \
                static_cast<unsigned>(ps)                               \
                ) |                                                     \
            _NXP_VAL2FLD(IOMUXC_SW_PAD_CTL_PAD_ ## pad ## _PE, pe) |    \
            _NXP_VAL2FLD(IOMUXC_SW_PAD_CTL_PAD_ ## pad ## _HYS, hys) |  \
            _NXP_VAL2FLD(IOMUXC_SW_PAD_CTL_PAD_ ## pad ## _SRE, sre) |  \
            _NXP_VAL2FLD(                                               \
                IOMUXC_SW_PAD_CTL_PAD_ ## pad ## _DSE,                  \
                static_cast<unsigned>(dse)                              \
                );                                                      \
    } while (0)


/**
 * \brief Configure IOMUX_LPSR MUX_CTL and PAD_CTL for the given pad.
 *
 * \param[in] pad
 *      The pad name.
 * \param[in] mux_mode
 *      MUX mode select.
 * \param[in] ps
 *      Pull up/down select; 0: 100K PD, 1: 5K PU, 2: 47K PU, 3: 100K PU
 * \param[in] pe
 *      Pull enable.
 * \param[in] hys
 *      Hysteresis enable; 0: disabled, 1: enabled
 * \param[in] sre
 *      Slew rate; 0: fast slew rate, 1: slow slow rate
 * \param[in] dse
 *      Drive strength; 0: X1, 1: X4, 2: X2, 3: X6
 */
#define iomux_lpsr_config_pad(pad, mux_mode, ps, pe, hys, sre, dse)     \
    do {                                                                \
        IOMUXC_LPSR->SW_MUX_CTL_PAD_ ## pad = (mux_mode);               \
        IOMUXC_LPSR->SW_PAD_CTL_PAD_ ## pad =                           \
            _NXP_VAL2FLD(                                               \
                IOMUXC_LPSR_SW_PAD_CTL_PAD_ ## pad ## _PS,              \
                static_cast<unsigned>(ps)                               \
                ) |                                                     \
            _NXP_VAL2FLD(IOMUXC_LPSR_SW_PAD_CTL_PAD_ ## pad ## _PE, pe) | \
            _NXP_VAL2FLD(IOMUXC_LPSR_SW_PAD_CTL_PAD_ ## pad ## _HYS, hys)|\
            _NXP_VAL2FLD(IOMUXC_LPSR_SW_PAD_CTL_PAD_ ## pad ## _SRE, sre)|\
            _NXP_VAL2FLD(                                               \
                IOMUXC_LPSR_SW_PAD_CTL_PAD_ ## pad ## _DSE,             \
                static_cast<unsigned>(dse)                              \
                );                                                      \
    } while (0)

/**
 * \brief Configure the SELECT_INPUT register for the given source. 
 *
 * \param[in] source
 *      Name of the source. The source name might be identical with the
 *      pad name. You have to check this with the reference manual
 *      from case to case.
 * \param[in] daisy
 *      The 'daisy'-chain setting according the reference manual.
 */
#define iomux_select_input(source, daisy) \
    IOMUXC_ ## source ## _SELECT_INPUT = (daisy)


} // namespace hodea

#endif /*!HODEA_IMX7_M4_PIN_CONFIG_HPP */
