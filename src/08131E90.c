#include "ffta.h"

typedef struct {
    u8 unknown_00[0xD6];
    u16 value;
} Unit;

typedef struct {
    Unit *source;
    u32 unknown_04;
    Unit *target;
    u16 action_id;
    u16 equipment_id;
    u8 unknown_10[0x10];
    s16 values[3];
    u16 flags;
    u8 selected;
} ActionState;

s32 func_080C7EA4(const void *object, u32 selector);

/* 0x08131E90..0x08131EC0: 48 bytes; add the selected adjustment to the
 * source unit's value and cap the result at ten. */
void func_08131E90(ActionState *state)
{
    s32 value = func_080C7EA4(state->source, 0x26)
                + state->values[state->selected];

    if (value > 10)
        value = 10;
    state->source->value = value;
}
