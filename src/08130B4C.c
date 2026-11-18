#include "ffta.h"

struct Unit {
    u8 unknown_00[9];
    u8 level;
};

struct ActionState {
    struct Unit *source;
    struct Unit *target;
};

extern u8 func_080C8280(const void *unit);

/* Action condition table 083A8604, slot 11. */
u8 func_08130B4C(struct ActionState *state)
{
    u8 eligible;

    if (func_080C8280(state->target))
        return 0;

    eligible = 0;
    if ((u8)(state->target->level % 3u) == 0)
        eligible = 1;
    return eligible;
}
