#include "ffta.h"

/* 0x0813EF34..0x0813EF38: 4 bytes. */
typedef struct {
    u8 unknown_00[0xA];
    u8 value;
} ByteState;

void func_0813EF34(ByteState *state, u8 value)
{
    state->value = value;
}
