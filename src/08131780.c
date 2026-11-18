#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 current;
} Unit;

typedef struct {
    Unit *source;
    Unit *target;
} ActionState;

extern u8 func_080CDA4C(const void *object);

/* Evaluator slot 21, [0x08131780, 0x081317BC). */
s32 func_08131780(ActionState *state)
{
    u16 current;
    u16 loss;

    if (func_080CDA4C(state->target))
        return 0;
    if (state->target->current <= 1)
        return 1;

    current = state->target->current;
    loss = current / 10u;
    if (!loss)
        loss = 1;
    return current - loss;
}
