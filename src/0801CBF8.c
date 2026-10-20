#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u8 *entries;
    u8 width;
} MapState;

u8 *func_0801CBF8(u8 column, u8 row)
{
    MapState *state = (MapState *)0x02007F10;

    return state->entries + row * state->width * 2 + column * 2;
}
