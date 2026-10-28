#include "ffta.h"

/* 0x0808B950..0x0808B984: 52 bytes, 26 instructions. */
void func_0808B950(u16 *destination, u16 tile, u16 width)
{
    s32 i;

    *destination++ = tile + 1;
    for (i = 1; i < width - 1; i++) {
        *destination++ = tile;
    }
    *destination = (tile + 1) | 0x400;
}
