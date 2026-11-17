#include "ffta.h"

// Target: complete [0x08003410, 0x08003454), 68 bytes, 27 instructions.
// Zero-fills BG VRAM with a 16-bit DMA3 fill, resets the affine OAM
// parameters, then zero-fills palette RAM the same way.

typedef struct {
    const void *source;
    void *destination;
    u32 control;
} DmaRegisters08003410;

extern DmaRegisters08003410 data_040000D4;

void func_08003454(void);

void func_08003410(void)
{
    u16 zero;

    {
        u16 *source = &zero;

        *source = 0;
        {
            /* plausible: DMA3 MMIO requires volatile writes and control readback. */
            volatile DmaRegisters08003410 *dma = &data_040000D4;

            dma->source = source;
            dma->destination = (void *)0x06000000;
            dma->control = 0x8100C000;
            (void)dma->control;
        }
    }

    func_08003454();

    {
        u16 *source = &zero;

        *source = 0;
        {
            /* plausible: DMA3 MMIO requires volatile writes and control readback. */
            volatile DmaRegisters08003410 *dma = &data_040000D4;

            dma->source = source;
            dma->destination = (void *)0x05000000;
            dma->control = 0x81000200;
            (void)dma->control;
        }
    }
}
