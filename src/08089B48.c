#include "ffta.h"

extern u32 func_0808B8E4(u32 window, u32 layer, u32 x, u32 y);

/* 0x08089B48..0x08089BA4: 92 bytes, 45 instructions. */
void func_08089B48(u32 window, u32 x, u32 y,
                    u16 filled, u16 total, u16 palette)
{
    u16 *destination;
    u32 position;
    u16 i;
    u16 empty;
    u16 attributes = palette;

    position = func_0808B8E4(window, 1, x, y);
    attributes <<= 12;
    destination = (u16 *)position;
    empty = total - filled;
    for (i = 0; i < total; i++) {
        if (i >= empty)
            *destination = attributes + 0xdb;
        else
            *destination = 0;
        destination++;
    }
}
