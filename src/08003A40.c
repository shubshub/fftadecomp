#include "ffta.h"

/* 0x08003A40-0x08003A6C: 44 bytes (40 bytes of code and a one-word literal pool).
 * Built at -O0: the r7 frame, the spills of the argument to [r7] and of the
 * entry to [r7, #4], their reloads and the register copies are -O0 code.  The
 * first 14 instructions are those of func_08003A08, which reads the same table.
 * data_0836D480 holds the four DMA channel register blocks (0x040000B0,
 * 0x040000BC, 0x040000C8, 0x040000D4); word 2 of a block is the channel's
 * control word. */
extern u32 *const data_0836D480[4];

void func_08003A40(u32 channel)
{
    u32 *dma = data_0836D480[channel];
    dma[2] = 0;
}
