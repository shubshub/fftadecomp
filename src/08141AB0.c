#include "ffta.h"

typedef u8 (*FlashReader)(u8 *address);

extern FlashReader data_0200F364;
extern u8 func_08141AAC(u8 *address);

/* FLASH512_V130 SetReadFlash1, 0x08141AB0..0x08141AEE (62 bytes). */
void func_08141AB0(u16 *destination)
{
    u16 *source;
    u16 count;

    data_0200F364 = (FlashReader)((u32)destination + 1);
    source = (u16 *)func_08141AAC;
    source = (u16 *)((u32)source ^ 1);
    count = ((s32)func_08141AB0 - (s32)func_08141AAC) >> 1;
    while (count != 0) {
        *destination++ = *source++;
        count--;
    }
}
