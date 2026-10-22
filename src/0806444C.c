#include "ffta.h"

void func_08013364(void);
void func_080610F8(u8 value);

void func_0806444C(void)
{
    ScriptState *state;

    func_08013364();
    func_080610F8(*(u8 *)&(*(ScriptState **)0x0200F450)->field_4e);
    state = *(ScriptState **)0x0200F450;
    state->current = state->entries[--state->count];
}
