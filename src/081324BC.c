#include "ffta.h"

struct Unit {
    u8 unknown_00[0x105];
    u8 value;
};

struct ActionState {
    u8 unknown_00[8];
    struct Unit *target;
    u8 unknown_0C[0x0C];
    u16 value;
};

/* Effect descriptor table 083A87B0, slot 34. */
void func_081324BC(struct ActionState *state)
{
    state->value = state->target->value;
}
