#include "ffta.h"

/* func_080B50F0: complete target [0x080B50F0, 0x080B5276), 390 bytes,
 * 195 instructions. */

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

s32 abs(s32 value);

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

u8 func_080B50F0(Selection *selection, u16 buttons, u8 x, u8 y)
{
    u8 initial_distance = 0;
    s8 direction;
    s32 index;
    s32 found;

    if (selection->count == 0)
        return 0;

    direction = 0;
    if (buttons & 0x200)
        direction = -1;
    if (buttons & 0x100)
        ++direction;
    if (direction == 0)
        return 0;

    for (index = 0; index < selection->count; ++index) {
        if (select_item_at(selection, index, x, y)) {
            selection->selected += direction;
            if (selection->selected < 0)
                selection->selected = selection->count - 1;
            if (selection->selected >= selection->count)
                selection->selected = 0;
            return 1;
        }
    }

    if (selection->reset_selection == 0) {
        found = -1;
        for (index = 0; index < selection->count; ++index) {
            if (found < 0) {
                found = index;
                initial_distance =
                    abs((s8)x - (selection->items[found]->x >> 5)) +
                    abs((s8)x - (selection->items[found]->y >> 5));
            } else {
                u8 current_distance =
                    abs((s8)x - (selection->items[index]->x >> 5)) +
                    abs((s8)x - (selection->items[index]->y >> 5));
                if ((s8)current_distance < (s8)initial_distance)
                    found = index;
            }
        }

        if (found >= 0) {
            selection->selected = found;
            return 1;
        }
    } else {
        selection->selected = 0;
        return 1;
    }
    return 0;
}
