#include "ffta.h"

void func_080648A0(void)
{
    u8 *control = (u8 *)0x03000ED0;
    ScriptState **state_slot = (ScriptState **)0x0200F450;
    ScriptState *state;

    control[5] = 1;
    if ((*state_slot)->unknown_52[0] == 0) {
        Record *record = (Record *)0x020020D0;

        record->field_0c = 0x1C;
    } else {
        Record *record = (Record *)0x020020D0;

        record->field_0c = 0x1B;
    }
    (*state_slot)->unknown_4d = 0x0B;
    (*state_slot)->unknown_51 = 0x5A;
    state = *state_slot;
    state->current = 0x3F;
    state->entries[state->count++] = 0x3F;
    state->current = 0x37;
    state->entries[state->count++] = 0x37;
    state->current = 0x31;
}
