#include "ffta.h"

/* Target: complete [0x0802CA58, 0x0802CABC), 100 bytes, 47 instructions. */
void func_0802CA58(u16 *tiles)
{
    s32 i;

    for (i = 6; i < 10; i++) {
        tiles[i] = (tiles[i] & 0x0fff) + 0xd000;
        tiles[i + 17] = (tiles[i + 17] & 0x0fff) + 0xd000;
    }
    for (i = 11; i < 16; i++) {
        tiles[i] = (tiles[i] & 0x0fff) + 0xd000;
        tiles[i + 17] = (tiles[i + 17] & 0x0fff) + 0xd000;
    }
}
