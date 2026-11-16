#include "ffta.h"

// Target: 0x08000718..0x08000788, complete 112-byte body including the
// literal pools (43 instructions).  Built at -O0, like its boot-module
// siblings 080006D0 and 08003A40: every local lives in an r7 frame slot.
// Upload the I/O register shadow (0x03000942, BG0CNT..BLDY) to 0x04000008
// with DMA0 (16-bit, 39 halfwords), wait for the channel, then copy the
// DISPCNT shadow at 0x03000940 to 0x03002BBC.
// The source pointer is a variable: the ROM stores it to [r7] at 0x08000720
// and reloads it at 0x08000728.  The two blocks are the DMA set and the DMA
// wait, each with its own register pointer: 0x08000746 stores 0x040000B0 to
// [r7, #4] a second time before the poll.
void func_08000718(void)
{
    u16 *src = (u16 *)0x03000942;
    {
        /* plausible: DMA0 registers at 0x040000B0 are MMIO hardware; the ROM reads DMA0CNT back at 0x08000744. */
        volatile u32 *dmaRegs = (volatile u32 *)0x040000B0;
        dmaRegs[0] = (u32)src;
        dmaRegs[1] = 0x04000008;
        dmaRegs[2] = 0x80000027;
        dmaRegs[2];
    }
    {
        /* plausible: DMA0 registers at 0x040000B0 are MMIO hardware polled for completion. */
        volatile u32 *dmaRegs = (volatile u32 *)0x040000B0;
        while (dmaRegs[2] & 0x80000000)
            ;
    }
    *(u16 *)0x03002BBC = *(u16 *)0x03000940;
}
