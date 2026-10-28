#include "ffta.h"

/* Target: complete [0x08149384, 0x081493AA), 38 bytes. */
u8 func_08149384(const u8 *tiles, u8 x, u8 y)
{
    const u8 *tile = tiles + ((y << 4) + x) * 7;

    if (tile[2] & 0x80)
        return 1;
    return 0;
}
