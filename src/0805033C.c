#include "ffta.h"

typedef struct {
    u8 unknown_000[0x560];
    u8 group;
    u8 unknown_561;
    u8 column;
    u8 row;
} SelectionState;

typedef struct {
    SelectionState *state;
} SelectionObject;

/* 0805033C..08050392: 86 bytes. */
u8 func_0805033C(SelectionObject *object, u16 buttons)
{
    u8 selection = object->state->column;
    u32 maximum = 5;

    if (object->state->group == 0x10) {
        if (object->state->row == 2)
            return selection;
    }

    if (buttons & 0x10) {
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
