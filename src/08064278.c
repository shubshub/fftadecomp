#include "ffta.h"

void func_08064278(void)
{
    ScriptState *state = *(ScriptState **)0x0200F450;

    state->current = 0x30;
    state->entries[state->count++] = 0x30;
    state->current = 0x39;
    state->entries[state->count++] = 0x39;
    state->current = 0x3B;
    state->entries[state->count++] = 0x3B;
    state->current = 0x34;
    state->entries[state->count++] = 0x34;
    state->current = 0x35;
}
