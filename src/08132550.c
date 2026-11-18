#include "ffta.h"

struct ActionState {
    u8 unknown_00[0x26];
    u16 flags;
};

/* Effect descriptor table 083A87B0, slot 39. */
void func_08132550(struct ActionState *state)
{
    state->flags |= 0x20;
}
