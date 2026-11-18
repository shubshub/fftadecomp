#include "ffta.h"

/* Action evaluator slot 4, 0x0813151C..0x08131544.
 * 10b5041c60689cf793fa0006002801d0002006e06068018b4808081a002800dc012010bc02bc0847
 */
struct Unit {
    u8 unknown00[0x18];
    u16 value;
};

struct ActionState {
    struct Unit *source;
    struct Unit *target;
};

extern u8 func_080CDA4C(const void *object);

s32 func_0813151C(struct ActionState *state)
{
    s32 result;
    u16 value;

    if (func_080CDA4C(state->target))
        return 0;

    value = state->target->value;
    result = value - value / 2;
    if (result < 1)
        result = 1;
    return result;
}
