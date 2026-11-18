#include "ffta.h"

struct Unit;
struct ActionState {
    struct Unit *entry;
    struct Unit *unit;
};

extern u8 func_080C8280(const void *unit);

/* Action condition table 083A8604, slot 18. */
u8 func_08130D00(struct ActionState *state)
{
    if (func_080C8280(state->unit))
        return 0;
    return state->entry != state->unit;
}
