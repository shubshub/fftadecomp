#include "ffta.h"

typedef struct {
    u8 unknown_000[0x560];
    u8 mode;
    u8 unknown_561[2];
    u8 selection;
} SelectionState;

typedef struct {
    SelectionState *state;
} SelectionObject;

/* 08050394..080503E2: 78 bytes. */
u8 func_08050394(SelectionObject *object, u16 buttons)
{
    u8 selection = object->state->selection;
    u32 maximum = 2;

    if (object->state->mode == 0x10)
        maximum = 1;

    if (buttons & 0x80) {
        if (selection < maximum)
            selection++;
        else
            selection = 0;
    } else {
        if (selection != 0)
            selection--;
        else
            selection = maximum;
    }

    return selection;
}
