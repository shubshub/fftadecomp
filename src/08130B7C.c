#include "ffta.h"

struct Unit {
    u8 unknown_00[9];
    u8 level;
};

struct ActionState {
    u8 unknown_00[4];
    struct Unit *unit;
};

extern u8 func_080C8280(const void *unit);
extern u8 func_081308F4(const struct Unit *unit);

/* Action condition table 083A8604, slot 12. */
u8 func_08130B7C(struct ActionState *state)
{
    u8 eligible;

    if (func_080C8280(state->unit) || func_081308F4(state->unit))
        return 0;

    eligible = 0;
    if ((u8)(state->unit->level % 5u) == 0)
        eligible = 1;
    return eligible;
}
