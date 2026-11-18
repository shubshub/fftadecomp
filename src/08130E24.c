#include "ffta.h"

struct Unit;
struct ActionState {
    struct Unit *entry;
    struct Unit *unit;
};

extern u8 func_080CDBCC(const struct Unit *unit);
extern u8 func_08130CC4(struct ActionState *state);

/* Action condition table 083A8604, slot 25. */
u8 func_08130E24(struct ActionState *state)
{
    if (func_080CDBCC(state->unit))
        return 0;
    return func_08130CC4(state);
}
