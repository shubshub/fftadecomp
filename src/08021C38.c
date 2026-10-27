#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u8 value;
} ValueState;

/* 08021C38..08021C3C: 4 bytes, 2 instructions. */
void func_08021C38(ValueState *state, u8 value)
{
    state->value = value;
}
