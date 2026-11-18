#include "ffta.h"

struct Unit;
struct ActionState {
    u8 unknown_00[4];
    struct Unit *unit;
};

extern u8 func_080C8298(const struct Unit *unit);

/* Action condition table 083A8604, slot 28. */
u8 func_08130FA4(struct ActionState *state)
{
    if (func_080C8298(state->unit))
        return 1;
    return 0;
}
