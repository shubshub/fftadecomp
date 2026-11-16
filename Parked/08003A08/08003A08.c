#include "ffta.h"

/* 0x08003A08-0x08003A3E: 54 bytes (50 bytes of code and a one-word literal pool).
 * Built at -O0, like func_08003A40 (src/08003A40.c), whose first 14 instructions
 * are this function's: the r7 frame, the spills of the argument to [r7] and of
 * the entry to [r7, #4], their reloads and the register copies are -O0 code.
 * data_0836D480 holds the four DMA channel register blocks (0x040000B0,
 * 0x040000BC, 0x040000C8, 0x040000D4); word 2 of a block is the channel's
 * control word, whose bit 31 stays set while the channel is enabled. */
extern u32 *const data_0836D480[4];

void func_08003A08(u32 channel)
{
    u32 *dma = data_0836D480[channel];
    while (dma[2] & 0x80000000)
        ;
}
