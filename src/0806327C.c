#include "ffta.h"

extern ScriptState *data_0200F450;
extern void func_08013364(void);

/* State dispatcher table 0x08393918, slot 22. */
void func_0806327C(void)
{
    ScriptState *state;

    func_08013364();
    state = data_0200F450;
    state->current = 0x17;
    state->entries[state->count++] = state->current;
    state->current = 0x34;
}
