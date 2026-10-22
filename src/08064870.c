#include "ffta.h"

typedef struct ScriptTaskState {
    u16 current;
    u16 count;
    u16 entries[32];
    void *task;
    u8 unknown_48[5];
    u8 unknown_4d;
} ScriptTaskState;

void func_08066028(void *task);

void func_08064870(void)
{
    ScriptTaskState *state;

    func_08066028((*(ScriptTaskState **)0x0200F450)->task);
    state = *(ScriptTaskState **)0x0200F450;
    state->current = 0x3E;
    state->entries[state->count++] = 0x3E;
    state->current = 0x32;
}
