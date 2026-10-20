#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u8 *entries;
    u8 width;
} MapState;

u32 func_0801CC7C(u8 column, u8 row)
{
    u8 width;
    u8 height;
    u8 left;
    u8 top;
    MapState *state = (MapState *)0x02007F10;

    func_0801CD4C(&width, &height, &left, &top);
    if (column < left)
        return 0;
    if (row < top)
        return 0;
    if (column >= left + width)
        return 0;
    if (row >= top + height)
        return 0;

    return state->entries[row * state->width * 2 + column * 2] != 0;
}
