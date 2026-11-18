#include "ffta.h"

typedef struct {
    void *source;
    void *target;
} ActionTargets;

extern s32 func_080C7EA4(const void *object, u32 selector);

/* Evaluator slot 40, [0x08131A50, 0x08131A5E). */
s32 func_08131A50(ActionTargets *state)
{
    return func_080C7EA4(state->target, 0x14);
}
