#include "ffta.h"

/* 0x08121D40..0x08121D80: 64 bytes, 29 instructions. */
typedef struct {
    u8 unknown_00[0x10];
    u32 value;
} State;

extern State *data_020159CC;

void func_08121D40(u32 value, u8 selected)
{
    u32 mask = 0xFF;
    s32 index;

    for (index = 0; index < 4; index++, mask <<= 8) {
        if ((selected >> index) & 1)
            data_020159CC->value =
                (data_020159CC->value & ~mask) | (value & mask);
    }
}
