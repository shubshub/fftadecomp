#include "ffta.h"

extern ScriptState *data_0200F450;

/* Restore the preceding script state from the history. */
void func_08064108(void)
{
    ScriptState *state = data_0200F450;

    state->current = state->entries[--state->count];
}
