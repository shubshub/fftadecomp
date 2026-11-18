#include "ffta.h"

extern u16 data_03000942[];
extern u16 data_03002BBC;

/* DMA0 uploads the LCD shadow from BG0CNT through BLDY, 39 halfwords. */
void func_08000718(void)
{
    u16 *src = data_03000942;

    {
        /* plausible: DMA0 SAD, DAD and CNT are 32-bit MMIO registers. Read CNT back after enabling. */
        volatile u32 *dma = (volatile u32 *)0x040000B0;
        dma[0] = (u32)src;
        dma[1] = 0x04000008;
        dma[2] = 0x80000027;
        (void)dma[2];
    }
    {
        /* plausible: each test reads the current DMA0 enable bit. */
        volatile u32 *dma = (volatile u32 *)0x040000B0;
        while (dma[2] & 0x80000000)
            ;
    }

    /* func_08000788 restores DISPCNT from this saved halfword. */
    data_03002BBC = *(u16 *)0x03000940;
}
