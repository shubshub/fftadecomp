#include "ffta.h"

/* Complete [0x08068158, 0x080681C4): 108 bytes, 51 instructions. */
typedef struct {
    u8 unknown_00[0xb];
    s8 selected;
    u8 count;
    u8 unknown_0d[0xa7];
    u8 tiles[1];
} MenuState;

typedef struct {
    u8 unknown_00[0x14];
    u16 *tiles;
} GraphicsState;

extern GraphicsState data_030008B0;

void func_08068158(MenuState *state)
{
    u16 *tiles = data_030008B0.tiles;
    u16 *top = tiles + 3;
    u16 *bottom = tiles + 35;
    s32 i;

    for (i = 0; i < state->count; ++i) {
        s32 palette = state->selected == i ? 15 : 9;
        u16 tile = state->tiles[i] * 4 + 0xa0;
        top[0] = tile++ + (palette << 12);
        top[1] = tile++ + (palette << 12);
        bottom[0] = tile++ + (palette << 12);
        bottom[1] = tile + (palette << 12);
        bottom += 2;
        top += 2;
    }
}
