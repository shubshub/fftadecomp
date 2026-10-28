#include "ffta.h"

/* 0x0813F124..0x0813F12C: 8 bytes. */
typedef struct {
    u32 value;
    u8 status;
} ValueState;

void func_0813F124(ValueState *state)
{
    state->value = 0;
    state->status = 0;
}
