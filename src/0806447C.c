#include "ffta.h"

void func_08013364(void);

void func_0806447C(void)
{
    ScriptState *state;

    func_08013364();
    state = *(ScriptState **)0x0200F450;
    state->current = state->entries[--state->count];
}
