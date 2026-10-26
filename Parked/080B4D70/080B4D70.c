#include "ffta.h"

/* 0x080B4D70: 120 bytes. */
typedef struct {
    u32 unknown_00[2];
    s16 x;
    u16 unknown_0A;
    s16 y;
} TileObject;

typedef struct {
    u32 unknown_00;
    TileObject *objects[20];
    u8 unknown_54;
    s8 selected;
    s8 count;
} TileSelection;

void func_080B4D70(TileSelection *selection, u8 x, u8 y)
{
    s32 i;

    for (i = 0; i < selection->count; i++) {
        TileObject *object = selection->objects[i];

        if ((object->x >> 5) == (s8)x && (object->y >> 5) == (s8)y) {
            selection->selected = i;
            {
                s8 *count = &selection->count;

                if (selection->selected < 0)
                    selection->selected = selection->count - 1;
                if (selection->selected >= *count)
                    selection->selected = 0;
            }
            return;
        }
    }
}
