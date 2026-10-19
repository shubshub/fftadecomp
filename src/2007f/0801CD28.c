#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u8 *entries;
    u8 width;
} Struct0801CD28;

void func_0801CD28(u8 column, u8 row, u8 value)
{
    Struct0801CD28 *state = (Struct0801CD28 *)0x02007F10;
    s32 offset = state->width;
    u8 *entries;

    offset *= row;
    offset *= 2;
    entries = state->entries + offset;
    entries += column * 2;
    entries[1] = value;
}
