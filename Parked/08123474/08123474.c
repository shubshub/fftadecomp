#include "ffta.h"

// 0x08123474..0x081234B4: 64 bytes, 31 instructions.
// Script bytes 1 and 2 are packed endpoints (low nibble x, high nibble y);
// distinct endpoints that share a row or column are passed to func_08124974
// with script byte 3.

void func_08124974(u8 start_x, u8 start_y, u8 end_x, u8 end_y, u8 value);

u32 func_08123474(void *context, const u8 *script)
{
    u8 start_x;
    u8 start_y;
    u8 end_x;
    u8 end_y;
    s16 start = script[1];
    s16 end = script[2];

    if ((u8)start == (u8)end)
        return 0x110;

    start_x = start & 0xF;
    start_y = (u8)start >> 4;
    end_x = end & 0xF;
    end_y = (u8)end >> 4;

    if (start_x == end_x || start_y == end_y)
        func_08124974(start_x, start_y, end_x, end_y, script[3]);
    return 0x110;
}
