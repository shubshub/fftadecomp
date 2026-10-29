#include "ffta.h"

typedef struct {
    const void *source;
    void *destination;
    u32 control;
} DmaRegisters08147A44;

extern DmaRegisters08147A44 data_040000B0;
extern u8 data_03003860[];

/* Complete [0x08147A44, 0x08147A7C): 56 bytes, 21 instructions. */
void func_08147A44(void)
{
    /* plausible: DMA0 MMIO requires word writes, control readback and completion polling. */
    volatile DmaRegisters08147A44 *dma = &data_040000B0;

    dma->source = data_03003860;
    dma->destination = (void *)0x05000000;
    dma->control = 0x84000100;
    (void)dma->control;
    while (dma->control & 0x80000000)
        ;
}
