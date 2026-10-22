#include "ffta.h"

typedef struct ScriptTaskTransitionState {
    u16 current;
    u16 count;
    u16 entries[32];
    void *task;
    u8 unknown_48[5];
    u8 unknown_4d;
    u8 unknown_4e[3];
    u8 unknown_51;
    u8 unknown_52;
} ScriptTaskTransitionState;

void func_08066028(void *task);
void func_081416DC(u16 value);

void func_08064914(void)
{
    ScriptTaskTransitionState *state;

    func_08066028((*(ScriptTaskTransitionState **)0x0200F450)->task);
    func_081416DC(0x0F);
    state = *(ScriptTaskTransitionState **)0x0200F450;
    if (state->unknown_52 == 0) {
        state->current = 0x44;
        state->entries[state->count++] = state->current;
        state->current = 0x34;
        state->entries[state->count++] = state->current;
        state->current = 0x36;
        state->entries[state->count++] = state->current;
        state->current = 0x32;
    } else {
        ScriptTaskTransitionState *resumed_state;

        state->unknown_51 = 0x10;
        resumed_state = *(ScriptTaskTransitionState **)0x0200F450;
        resumed_state->current = resumed_state->entries[--resumed_state->count];
        resumed_state->entries[resumed_state->count++] = resumed_state->current;
        resumed_state->current = 0x32;
    }
}
