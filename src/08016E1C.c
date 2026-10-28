#include "ffta.h"

typedef struct BlockState08016E1C {
    u8 unknown_00[0x1C];
    u8 flags;
    u8 first;
    u8 second;
} BlockState08016E1C;

/* Complete [0x08016E1C, 0x08016E4C): 48 bytes, 24 instructions. */
void func_08016E1C(BlockState08016E1C *state, u8 first, u8 second)
{
    if (first == 0 && second == 0) {
        state->flags &= ~2;
    } else {
        state->flags |= 2;
        state->first = first;
        state->second = second;
    }
}
