#include "ffta.h"

struct Position080B7EA0 {
    u8 x;
    u8 y;
    u8 height;
    u8 unknown03;
};

/* Complete [0x080B7EA0, 0x080B7EDC): 60 bytes, 30 instructions. */
s32 func_080B7EA0(const struct Position080B7EA0 *positions, s32 count,
                  s8 x, s8 y)
{
    s32 i;

    for (i = 0; i < count; i++, positions++) {
        if (x == positions->x && y == positions->y)
            return 1;
    }
    return 0;
}
