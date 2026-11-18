#include "ffta.h"

struct Unit;
struct ActionState {
    u8 unknown_00[4];
    struct Unit *unit;
};

extern u8 func_080C8280(const void *unit);
extern u8 func_080C8384(const struct Unit *unit);

/* Action condition table 083A8604, slot 20. */
u8 func_08130D54(struct ActionState *state)
{
    if (func_080C8280(state->unit))
        return 0;
    return !func_080C8384(state->unit);
}
