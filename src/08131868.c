#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 current;
    u16 maximum;
} UnitValues;

typedef struct {
    UnitValues *source;
    UnitValues *target;
} ActionState;

extern u8 func_080CDA4C(const void *object);

/* Evaluator slot 26, [0x08131868, 0x08131890). */
s32 func_08131868(ActionState *state)
{
    s32 difference;

    if (func_080CDA4C(state->target))
        return 0;
    difference = state->source->maximum - state->source->current;
    if (difference <= 1)
        difference = 0;
    return difference;
}
