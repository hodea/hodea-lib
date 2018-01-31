// Copyright (c) 2017, Franz Hollerer.
// SPDX-License-Identifier: MIT

/**
 * Bootloader support functions for STM32 devices.
 *
 * \author f.hollerer@hodea.org
 */
#include <hodea/core/bitmanip.hpp>
#include <hodea/device/hal/device_setup.hpp>
#include <hodea/device/hal/bls.hpp>

namespace hodea {

/**
 * Calculate CRC over program memory.
 *
 * This function uses the built-in CRC unit and DMA channel 1 to
 * calculate the CRC value over the given program memory.
 *
 * The used CRC has the following properties:
 *   Width        = 32
 *   Poly         = 0x4C11DB7
 *   XorIn        = 0xffffffff
 *   ReflectIn    = False
 *   XorOut       = 0
 *   ReflectOut   = False
 *
 * \param[in] start
 *      Start address for CRC calculation.
 * \param[in] end
 *      End address for CRC calculation.
 *
 * @returns
 *      CRC calculated from \a start to \a end (inclusive).
 */
uint32_t bls_progmem_crc(const uint32_t *start, const uint32_t *end)
{
    uint32_t crc;
    DMA_Channel_TypeDef *dma = DMA1_Channel1;
    uint32_t ahbenr_ori;

    // enable required peripheral clocks
    ahbenr_ori = RCC->AHBENR;
#if defined RCC_AHBENR_DMAEN
    set_bit(RCC->AHBENR, RCC_AHBENR_CRCEN | RCC_AHBENR_DMAEN);
#else
    set_bit(RCC->AHBENR, RCC_AHBENR_CRCEN | RCC_AHBENR_DMA1EN);
#endif

    // reset CRC unit to its default settings
    CRC->CR = 0;
    set_bit(CRC->CR, CRC_CR_RESET);

    // set up DMA transfer to CRC unit over program memory
    dma->CCR =
        _VAL2FLD(DMA_CCR_MEM2MEM, 1) |
        _VAL2FLD(DMA_CCR_PL, 3) |
        _VAL2FLD(DMA_CCR_MSIZE, 2) |
        _VAL2FLD(DMA_CCR_PSIZE, 2) |
        _VAL2FLD(DMA_CCR_MINC, 1) |
        _VAL2FLD(DMA_CCR_PINC, 0) |
        _VAL2FLD(DMA_CCR_DIR, 1);

    dma->CNDTR = end - start + 1;

    dma->CPAR = (uintptr_t) &CRC->DR;
    dma->CMAR = (uintptr_t) start;

    set_bit(dma->CCR, DMA_CCR_EN);

    // wait DMA transfer and therefore CRC calculation is complete. 
    while (!is_bit_set(DMA1->ISR, DMA_ISR_TCIF1)) ;

    set_bit(DMA1->IFCR, DMA_IFCR_CTCIF1);
    clr_bit(dma->CCR, DMA_CCR_EN);

    crc = CRC->DR;

    // restore original peripheral clock settings
    RCC->AHBENR = ahbenr_ori;

    return crc;
}

} // namespace hodea

