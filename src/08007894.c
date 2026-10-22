#include "ffta.h"

typedef struct CompletionState {
    u8 unknown_00[0x14];
    s16 remaining;
} CompletionState;

u32 func_08007894(const void *state)
{
    const CompletionState *completion = state;
    u32 result = 0;

    if (completion->remaining <= 0) {
        result = 1;
    }
    return result;
}
