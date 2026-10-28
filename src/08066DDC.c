#include "ffta.h"

typedef struct {
    u16 *primary;
    u16 *secondary;
    u8 unknown_08[8];
    u8 x;
    u8 y;
    u8 outer_width;
    u8 unknown_13;
    u16 value;
    u8 stride;
    u8 mode;
    u16 first;
    u16 last;
    u8 flags;
    u8 unknown_1D[2];
    u8 alignment;
    u16 width;
    u16 height;
    s16 expected_width;
    s16 expected_height;
} TileRegion08066DDC;

typedef struct {
    u8 unknown_00[8];
    u8 phase;
    u8 unknown_09[0x1b];
    TileRegion08066DDC region;
} Menu08066DDC;

extern u8 func_08017180(TileRegion08066DDC *region);
extern void func_08068158(Menu08066DDC *menu);
extern void func_080681C4(Menu08066DDC *menu);

/* Complete target [0x08066DDC, 0x08066E08): 44 bytes, 19 instructions. */
u8 func_08066DDC(Menu08066DDC *menu)
{
    u8 complete = func_08017180(&menu->region);

    if (complete && menu->phase == 4) {
        func_08068158(menu);
        func_080681C4(menu);
    }
    return complete;
}
