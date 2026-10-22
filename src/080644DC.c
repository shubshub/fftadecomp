#include "ffta.h"

void func_080C71B4(u16 value);

void func_080644DC(void)
{
    ScriptState **state_slot = (ScriptState **)0x0200F450;
    ScriptState *state;

    func_080C71B4((*state_slot)->unknown_50);
    state = *state_slot;
    state->current = state->entries[--state->count];
}
