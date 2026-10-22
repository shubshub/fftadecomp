/* 0x08007880 - 18 bytes
 * Target: 00b5 0021 806a 0028 00dc 0121 081c 02bc 0847
 */
#include "ffta.h"

typedef struct CompletionState {
    u8 unknown_00[0x28];
    s32 remaining;
} CompletionState;

u32 func_08007880(const void *state)
{
    const CompletionState *completion = state;
    u32 result = 0;

    if (completion->remaining <= 0) {
        result = 1;
    }
    return result;
}
