#include "ffta.h"

struct Unit;
struct ActionState {
    u8 unknown_00[4];
    struct Unit *unit;
};

extern u8 func_080C8280(const void *unit);
extern u8 func_081308F4(const struct Unit *unit);

/* Action condition table 083A8604, slot 22. */
u8 func_08130DA8(struct ActionState *state)
{
    if (func_080C8280(state->unit))
        return 0;
    return func_081308F4(state->unit);
}
