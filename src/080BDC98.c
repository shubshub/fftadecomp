#include "ffta.h"

/* Complete [0x080BDC98, 0x080BDCAC): 20 bytes, 10 instructions. */
void func_080BDC98(s32 *grid, u8 column, u8 row)
{
    u32 offset = column * sizeof(s32) + row * 16 * sizeof(s32);
    s32 *cell = (s32 *)((u8 *)grid + offset);

    *cell = -1;
}
