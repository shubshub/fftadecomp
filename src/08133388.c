#include "ffta.h"

typedef struct {
    u8 unknown_00[0x26];
    u16 flags;
} ActionState;

void func_08133388(ActionState *state)
{
    state->flags |= 0x20;
}
