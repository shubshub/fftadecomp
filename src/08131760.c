#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1A];
    u16 value;
} Unit08131760;

typedef struct {
    Unit08131760 *source;
    Unit08131760 *target;
} ActionState08131760;

extern u8 func_080CDA4C(const void *object);

/* Evaluator slot 20, [0x08131760, 0x0813177E). */
s32 func_08131760(ActionState08131760 *state)
{
    if (func_080CDA4C(state->target))
        return 0;
    return state->target->value;
}
