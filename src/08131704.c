#include "ffta.h"

struct ActionState;

extern s32 func_081314FC(struct ActionState *state);

/* Evaluator slot 14, [0x08131704, 0x0813170E). */
s32 func_08131704(struct ActionState *state)
{
    return func_081314FC(state);
}
