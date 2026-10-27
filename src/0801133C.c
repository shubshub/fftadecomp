#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    void *value;
    u8 unknown_08[0x0C];
    u16 flags;
} ValueState;

/* 0801133C..08011348: 12 bytes, 6 instructions. */
void func_0801133C(ValueState *state, void *value)
{
    state->value = value;
    state->flags |= 6;
}
