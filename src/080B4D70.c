#include "ffta.h"

/* func_080B4D70: complete target [0x080B4D70, 0x080B4DE8), 120 bytes,
 * 60 instructions:
 * 30 b5 84 46 09 06 09 0e 12 06 12 0e 00 23 64 46
 * 56 34 00 20 20 56 83 42 2b da 08 06 05 16 10 06
 * 02 16 98 00 61 46 04 31 09 18 09 68 08 89 00 04
 * 40 15 a8 42 18 d1 88 89 00 04 40 15 90 42 13 d1
 * 62 46 55 32 00 25 13 70 18 06 63 46 56 33 00 28
 * 02 da 20 78 01 38 10 70 00 21 51 56 00 20 18 56
 * 81 42 06 db 15 70 04 e0 01 33 00 20 20 56 83 42
 * d7 db 30 bc 01 bc 00 47
 *
 * Selects the listed item standing on tile (x, y), then wraps the selection
 * into [0, count) the way func_080B50F0 does after its step. */

typedef struct {
    u8 unknown_00[8];
    s16 x;
    u8 unknown_0A[2];
    s16 y;
} Item;

typedef struct {
    u32 unknown_00;
    Item *items[13];
    u8 unknown_38[0x1D];
    s8 selected;
    s8 count;
    u8 reset_selection;
} Selection;

static inline s32 select_item_at(Selection *selection, s32 index, s8 x, s8 y)
{
    Item *item = selection->items[index];

    if ((item->x >> 5) != x)
        return 0;
    if ((item->y >> 5) != y)
        return 0;
    selection->selected = index;
    return 1;
}

void func_080B4D70(Selection *selection, s8 x, s8 y)
{
    s32 index;

    for (index = 0; index < selection->count; ++index) {
        if (select_item_at(selection, index, x, y)) {
            if (selection->selected < 0)
                selection->selected = selection->count - 1;
            if (selection->selected >= selection->count)
                selection->selected = 0;
            return;
        }
    }
}
