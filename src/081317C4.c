#include "ffta.h"

struct ActionState {
    void *source;
    void *target;
};

extern u8 func_080CDA4C(const void *object);
extern s32 func_080C7EA4(const void *object, u32 selector);

/* Evaluator slot 23, [0x081317C4, 0x08131804). */
s32 func_081317C4(struct ActionState *state)
{
    s32 value;

    if (func_080CDA4C(state->target))
        return 0;
    value = func_080C7EA4(state->target, 0x39) * 10;
    if (value < -999)
        value = -999;
    if (value > 999)
        value = 999;
    return value;
}
