#include "ffta.h"

/* Action evaluator slot 5, 0x08131544..0x0813156A.
 * 10b5041c60689cf77ffa0006002801d0002005e06068008b8008002800dc012010bc02bc0847
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

s32 func_08131544(struct ActionState *state)
{
    s32 result;

    if (func_080CDA4C(state->target))
        return 0;

    result = state->target->value / 4;
    if (result < 1)
        result = 1;
    return result;
}
