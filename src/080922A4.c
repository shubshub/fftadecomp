#include "ffta.h"

/* Complete [0x080922A4, 0x080922C2): 30 bytes, 15 instructions. */
typedef struct {
    u8 unknown_00[0x0e];
    s16 limit;
    u8 unknown_10[8];
    const u8 *data;
} ComparisonState;

s32 func_080922A4(const ComparisonState *state)
{
    u8 low = state->data[0];
    u8 high = state->data[1];
    s32 value = (high << 8) | low;
    if (value > state->limit)
        return 0;
    return 1;
}
