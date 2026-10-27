#include "ffta.h"

/* 0x08003A08..0x08003A3E: 54 bytes. */
typedef struct {
    u32 source;
    u32 destination;
    u32 control;
} DmaRegisters08003A08;

/* plausible: hardware-register: this ROM table contains DMA0..DMA3 MMIO
 * addresses 0x040000B0, 0x040000BC, 0x040000C8 and 0x040000D4. */
extern volatile DmaRegisters08003A08 *const data_0836D480[];

void func_08003A08(u32 channel)
{
    /* plausible: hardware-register: DMA control bit 31 remains set while
     * the selected hardware channel is enabled; each poll reads MMIO. */
    volatile DmaRegisters08003A08 *dma = data_0836D480[channel];
    u32 busy;

    do {
        busy = dma->control & 0x80000000;
    } while (busy != 0);
}
