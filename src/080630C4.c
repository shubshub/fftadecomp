#include "ffta.h"

extern ScriptState *data_0200F450;

/* State dispatcher table 0x08393918, slot 19. */
void func_080630C4(void)
{
    ScriptState *state;

    data_0200F450->unknown_4d = 2;
    state = data_0200F450;
    state->current = 0x14;
    state->entries[state->count++] = state->current;
    state->current = 0x31;
}
