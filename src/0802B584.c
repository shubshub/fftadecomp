#include "ffta.h"

typedef struct {
    u8 unknown_00[0x799];
    u8 value;
} FieldState;

/* 0x0802B584..0x0802B590: 12 complete bytes, including the field-offset literal. */
void func_0802B584(FieldState *state, u8 value)
{
    state->value = value;
}
