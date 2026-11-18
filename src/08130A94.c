#include "ffta.h"

struct Unit;

struct ActionState {
    struct Unit *source;
    struct Unit *target;
};

extern u8 func_080C8280(const void *unit);

/* Action condition table 083A8604, slot 8. */
u8 func_08130A94(struct ActionState *state)
{
    if (func_080C8280(state->target))
        return 0;
    return 1;
}
