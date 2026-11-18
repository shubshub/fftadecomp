#include "ffta.h"

typedef struct {
    void *source;
    void *target;
} ActionTargets;

extern s32 func_080C7EA4(const void *object, u32 selector);

/* Evaluator slot 41, [0x08131A60, 0x08131A76). */
s32 func_08131A60(ActionTargets *state)
{
    s32 result = (u32)func_080C7EA4(state->target, 0x14) >> 1;

    if (result < 1)
        result = 1;
    return result;
}
