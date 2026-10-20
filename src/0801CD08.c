#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u8 *entries;
    u8 width;
} MapState;

u8 func_0801CD08(u8 column, u8 row)
{
    MapState *state = (MapState *)0x02007F10;
    s32 offset = state->width;
    u8 *entries;

    offset *= row;
    offset *= 2;
    entries = state->entries + offset;
    entries += column * 2;
    return entries[1];
}
