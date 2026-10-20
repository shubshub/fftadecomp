#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u8 *entries;
    u8 width;
} MapState;

s16 func_0801CC38(u8 column, u8 row, u8 mode)
{
    MapState *state = (MapState *)0x02007F10;
    s32 offset = row * state->width;
    u8 *entries;
    s16 height;

    offset *= 2;
    entries = state->entries + offset;
    entries += column * 2;
    height = entries[0];
    if (!(mode & 1) && (entries[1] & 2))
        height--;
    return height;
}
