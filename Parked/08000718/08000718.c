#include "ffta.h"

typedef struct {
    const void *source;
    void *destination;
    u32 control;
} DmaRegisters;

extern u16 data_03000942[];
extern DmaRegisters data_040000B0;
extern u16 data_04000008;
extern u16 data_03002BBC;
extern u16 g_control_flags_03000940;

/* 0x08000718..0x08000788: transfer the shadow display registers through DMA0. */
void func_08000718(void)
{
    /* plausible: DMA0 hardware registers require volatile writes and completion reads. */
    volatile DmaRegisters *dma = &data_040000B0;

    dma->source = data_03000942;
    dma->destination = &data_04000008;
    dma->control = 0x80000027;
    (void)dma->control;
    while (dma->control & 0x80000000) {
    }
    data_03002BBC = g_control_flags_03000940;
}
