#include "ffta.h"

/* 0x0802DF90..0x0802DFCA: 58 bytes / 27 instructions. */
typedef struct {
    u8 unknown_00[0x102];
    u8 first;
    u8 second;
} CountState;

u8 func_0802DF90(const CountState *state)
{
    u8 count = state->second + state->first * 2;

    if (count < 3)
        return 0;
    if (count < 7)
        return 1;
    if (count < 12)
        return 2;
    return 3;
}
