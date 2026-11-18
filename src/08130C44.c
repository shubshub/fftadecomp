#include "ffta.h"

struct Unit;
struct ActionState {
    struct Unit *entry;
    struct Unit *unit;
};

extern u8 func_080C8280(const void *unit);
extern u8 func_080C8240(void *unit);

/* Action condition table 083A8604, slot 15. */
u8 func_08130C44(struct ActionState *state)
{
    u32 entry_flag;
    u32 unit_flag;

    if (func_080C8280(state->unit))
        return 0;
    entry_flag = func_080C8240(state->entry);
    unit_flag = func_080C8240(state->unit);
    return unit_flag != entry_flag;
}
