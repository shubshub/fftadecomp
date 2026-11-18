#include "ffta.h"

struct Unit;
struct ActionState {
    struct Unit *entry;
    struct Unit *unit;
};

extern u8 func_080C8280(const void *unit);
extern u8 func_080C8240(void *unit);
extern u8 func_080C8384(const struct Unit *unit);

/* Action condition table 083A8604, slot 16. */
u8 func_08130C80(struct ActionState *state)
{
    u32 entry_flag;
    u32 unit_flag;

    if (func_080C8280(state->unit))
        return 0;
    entry_flag = func_080C8240(state->entry);
    unit_flag = func_080C8240(state->unit);
    if (unit_flag != entry_flag && !func_080C8384(state->unit))
        return 1;
    return 0;
}
