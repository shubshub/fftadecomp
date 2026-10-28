#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    s16 count;
    s16 current;
} Selection08037F0C;

/* Complete [0x08037F0C, 0x08037F40): 52 bytes, 26 instructions. */
u16 func_08037F0C(const Selection08037F0C *selection, s8 offset)
{
    s16 index = selection->current + offset;
    u16 result;

    if (index < 0) {
        result = 0;
    } else if (index <= selection->count - 1) {
        result = index;
    } else {
        result = selection->count - 1;
    }
    return result;
}
