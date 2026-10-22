#include "ffta.h"

typedef struct ScriptTaskState {
    u16 current;
    u16 count;
    u16 entries[32];
    void *task;
    u8 unknown_48[5];
    u8 unknown_4d;
} ScriptTaskState;

void *func_08064FA0(u8 selector);

void func_08064354(void)
{
    void *task = func_08064FA0((*(ScriptTaskState **)0x0200F450)->unknown_4d);
    ScriptTaskState *state = *(ScriptTaskState **)0x0200F450;

    state->task = task;
    state->current = state->entries[--state->count];
}
