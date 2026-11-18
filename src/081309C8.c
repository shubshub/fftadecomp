#include "ffta.h"

typedef struct Unit Unit;

typedef struct ActionState {
    Unit *source;
    Unit *target;
    u8 unknown_08[0x1E];
    u16 flags;
} ActionState;

extern u8 func_080C8240(void *unit);
extern u8 func_080C8280(const void *unit);
extern u8 func_081308F4(const Unit *unit);

u8 func_081309C8(ActionState *state)
{
    u8 target_flag;

    if (func_080C8280(state->target) || func_081308F4(state->target))
        return 0;
    target_flag = func_080C8240(state->target);
    if (state->flags & 0x80) {
        if (!target_flag)
            return 0;
    } else if (target_flag) {
        return 0;
    }
    return 1;
}
