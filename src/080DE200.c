#include "ffta.h"

/* 0x080DE200..0x080DE20E: 14 bytes. */
typedef struct {
    u8 unknown_00[0x1F];
    s8 value;
} SignedValueState;

extern void func_080DE210(SignedValueState *state, s8 value);

void func_080DE200(SignedValueState *state)
{
    func_080DE210(state, state->value);
}
