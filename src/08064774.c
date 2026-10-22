#include "ffta.h"

void func_08064774(void)
{
    ScriptState *state = *(ScriptState **)0x0200F450;

    state->field_64 = 0x9002;
    state->field_66 = 0x1235;
    state->current = state->entries[--state->count];
}
