#include "ffta.h"

struct Unit {
    u8 unknown_00[6];
    u8 job;
};

struct ActionState {
    u8 unknown_00[4];
    struct Unit *unit;
};

extern u8 func_080C8280(const void *unit);

/* Action condition table 083A8604, slot 21. */
u8 func_08130D80(struct ActionState *state)
{
    if (func_080C8280(state->unit))
        return 0;
    return state->unit->job != 9;
}
