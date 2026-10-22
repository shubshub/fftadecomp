#include "ffta.h"

void func_080644A0(void)
{
    ScriptState *state;

    if ((*(ScriptState **)0x0200F450)->unknown_51 != 0)
        (*(ScriptState **)0x0200F450)->unknown_51--;

    state = *(ScriptState **)0x0200F450;
    if (state->unknown_51 == 0)
        state->current = state->entries[--state->count];
}
