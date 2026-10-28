#include "ffta.h"

/* Target: complete [0x08025D14, 0x08025D84), 112 bytes. */
typedef struct {
    u8 unknown_00[9];
    s8 visible_rows;
    u8 unknown_0a[0x7a];
    u16 count;
    u8 unknown_86[0x12];
    const u8 *enabled;
} SelectionList;

typedef struct {
    u16 first;
    u16 offset;
} SelectionPosition;

static inline void select_row(SelectionList *list,
                              SelectionPosition *position, s32 index)
{
    u16 first = position->first;

    if (index <= first) {
        position->first = index;
        position->offset = 0;
    } else {
        s32 last = first + list->visible_rows - 1;

        if (index <= last) {
            position->offset = index - first;
        } else {
            position->first = first + (index - last);
            position->offset = list->visible_rows - 1;
        }
    }
}

void func_08025D14(SelectionList *list, SelectionPosition *position)
{
    if (list->enabled && !list->enabled[position->first + position->offset]) {
        s32 index;

        for (index = 0; index < list->count; index++) {
            if (list->enabled[index]) {
                select_row(list, position, index);
                break;
            }
        }
    }
}
