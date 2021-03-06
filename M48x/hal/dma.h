/**************************************************************************//**
 * @file     dma.h
 * @version  V0.10
 * @brief   M480 dma functions
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef NU_DMA_H
#define NU_DMA_H


#ifdef __cplusplus
extern "C" {
#endif

#define DMA_CAP_NONE    (0 << 0)

#define DMA_EVENT_ABORT             (1 << 0)
#define DMA_EVENT_TRANSFER_DONE     (1 << 1)
#define DMA_EVENT_TIMEOUT           (1 << 2)
#define DMA_EVENT_ALL               (DMA_EVENT_ABORT | DMA_EVENT_TRANSFER_DONE | DMA_EVENT_TIMEOUT)
#define DMA_EVENT_MASK              DMA_EVENT_ALL

#define DMA_ERROR_OUT_OF_CHANNELS (-1)

typedef enum {
    DMA_USAGE_NEVER,
    DMA_USAGE_OPPORTUNISTIC,
    DMA_USAGE_ALWAYS,
    DMA_USAGE_TEMPORARY_ALLOCATED,
    DMA_USAGE_ALLOCATED
} DMAUsage;

int dma_channel_allocate(uint32_t capabilities);
int dma_channel_free(int channelid);
void dma_set_handler(int channelid, uint32_t handler, uint32_t id, uint32_t event);
void dma_unset_handler(int channelid);

PDMA_T *dma_modbase(void);
int dma_untransfer_bytecount(int channelid);

int dma_fill_description(
	int channelid, 
	uint32_t u32Peripheral, 
	uint32_t data_width, 
	uint32_t addr_src,		//For u32ScatterEn case, it is scatter gather table address
	uint32_t addr_dst, 
	int32_t length, 
	uint32_t timeout,
	uint32_t u32ScatterEn 
);

void dma_channel_terminate(int i32ChannID);

void Handle_PDMA_Irq(void);

#ifdef __cplusplus
}
#endif

#endif
