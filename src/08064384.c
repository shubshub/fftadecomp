#include "ffta.h"

typedef struct ScriptTaskState {
    u16 current;
    u16 count;
    u16 entries[32];
    void *task;
    u8 unknown_48[5];
    u8 unknown_4d;
} ScriptTaskState;

s16 func_08065050(const void *object);
void func_08066018(void *object);

void func_08064384(void)
{
    ScriptTaskState *state;

    if (func_08065050((*(ScriptTaskState **)0x0200F450)->task) != 0) {
        func_08066018((*(ScriptTaskState **)0x0200F450)->task);
        state = *(ScriptTaskState **)0x0200F450;
        state->current = state->entries[--state->count];
    }
}
