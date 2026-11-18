#include "ffta.h"

// Target: complete [0x08003410, 0x08003454), 68 bytes, 27 instructions.
// Zero-fills all 96 KiB of VRAM with a 16-bit DMA3 fill, resets the affine OAM
// parameters, then zero-fills palette RAM the same way.

/* DMA3 SAD, DAD and CNT are hardware registers. */
typedef struct {
    const void *source;
    void *destination;
    u32 control;
} DmaRegisters;

/* plausible: DMA3 requires ordered register writes and control readback. */
extern volatile DmaRegisters data_040000D4;

void func_08003454(void);

void func_08003410(void)
{
    u16 zero;

    {
        u16 *source = &zero;

        *source = 0;
        data_040000D4.source = source;
        data_040000D4.destination = (void *)0x06000000;
        data_040000D4.control = 0x8100C000;
        (void)data_040000D4.control;
    }

    func_08003454();

    {
        u16 *source = &zero;

        *source = 0;
        data_040000D4.source = source;
        data_040000D4.destination = (void *)0x05000000;
        data_040000D4.control = 0x81000200;
        (void)data_040000D4.control;
    }
}
