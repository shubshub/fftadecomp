#include "ffta.h"

extern u16 (*data_0200F368)(u8 phase, u8 *address, u8 lastData);

/* FLASH512_V130 ProgramByte. Unlock byte programming, write the source byte,
 * then wait for phase 1 to read that byte back from the destination. */
u16 func_08141FC8(u8 *source, u8 *destination)
{
    *(volatile u8 *)0x0E005555 = 0xAA;
    *(volatile u8 *)0x0E002AAA = 0x55;
    *(volatile u8 *)0x0E005555 = 0xA0;
    *destination = *source;
    return data_0200F368(1, destination, *source);
}
