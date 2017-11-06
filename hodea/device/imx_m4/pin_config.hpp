// Copyright (c) 2017, Franz Hollerer. All rights reserved.
// This code is licensed under the MIT License (MIT).
// See LICENSE file for full details.

/**
 * IOMUX - I/O multiplexer pin configuration support.
 *
 * \author f.hollerer@gmx.net
 */
#if !defined _HODEA_IMX_M4_PIN_CONFIG_HPP_
#define _HODEA_IMX_M4_PIN_CONFIG_HPP_

#include <hodea/device/hal/device_setup.hpp>

namespace hodea {

/**
 * \brief Constants for pull select field in IOMUX pad config.
 * @{
 */
#define PS_100K_PD  0U
#define PS_5K_PU    1U
#define PS_47K_PU   2U
#define PS_100K_PU  3U
/** @} */

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
#define IOMUX_CONFIG_PAD(pad, mux_mode, ps, pe, hys, sre, dse)          \
    do {                                                                \
        IOMUXC->SW_MUX_CTL_PAD_ ## pad = (mux_mode);                    \
        IOMUXC->SW_PAD_CTL_PAD_ ## pad =                                \
            _NXP_VAL2FLD(IOMUXC_SW_PAD_CTL_PAD_ ## pad ## _PS, ps) |    \
            _NXP_VAL2FLD(IOMUXC_SW_PAD_CTL_PAD_ ## pad ## _PE, pe) |    \
            _NXP_VAL2FLD(IOMUXC_SW_PAD_CTL_PAD_ ## pad ## _HYS, hys) |  \
            _NXP_VAL2FLD(IOMUXC_SW_PAD_CTL_PAD_ ## pad ## _SRE, sre) |  \
            _NXP_VAL2FLD(IOMUXC_SW_PAD_CTL_PAD_ ## pad ## _DSE, dse);   \
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
#define IOMUX_LPSR_CONFIG_PAD(pad, mux_mode, ps, pe, hys, sre, dse)     \
    do {                                                                \
        IOMUXC_LPSR->SW_MUX_CTL_PAD_ ## pad = (mux_mode);               \
        IOMUXC_LPSR->SW_PAD_CTL_PAD_ ## pad =                           \
            _NXP_VAL2FLD(IOMUXC_LPSR_SW_PAD_CTL_PAD_ ## pad ## _PS, ps) | \
            _NXP_VAL2FLD(IOMUXC_LPSR_SW_PAD_CTL_PAD_ ## pad ## _PE, pe) | \
            _NXP_VAL2FLD(IOMUXC_LPSR_SW_PAD_CTL_PAD_ ## pad ## _HYS, hys)|\
            _NXP_VAL2FLD(IOMUXC_LPSR_SW_PAD_CTL_PAD_ ## pad ## _SRE, sre)|\
            _NXP_VAL2FLD(IOMUXC_LPSR_SW_PAD_CTL_PAD_ ## pad ## _DSE, dse);\
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
#define IOMUX_SELECT_INPUT(source, daisy) \
    IOMUXC_ ## source ## _SELECT_INPUT = (daisy)


} // namespace hodea

#endif /*!_HODEA_IMX_M4_PIN_CONFIG_HPP_ */
