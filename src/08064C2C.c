#include "ffta.h"

typedef struct {
    u16 current;
    u16 count;
    u16 entries[34];
    u8 unknown_48[9];
    u8 unknown_51;
    u8 unknown_52[2];
    u32 flags;
} ScriptFlagState;

typedef struct {
    u8 unknown_0000[0x1F64];
    u32 resource;
} ResourceState;

extern u8 g_state_02000000[];

void func_08029F18(s32 delta, void *owner, u16 *scratch, s16 column, s16 row);

void func_08064C2C(void)
{
    ScriptFlagState *state;
    ResourceState *resources;

    (*(ScriptFlagState **)0x0200F450)->flags &= ~1;
    resources = (ResourceState *)g_state_02000000;
    if (resources->resource > 4999) {
        func_08029F18(-5000, (void *)0x030008B0, 0, 20, 16);
        resources->resource -= 5000;
        (*(ScriptFlagState **)0x0200F450)->flags |= 0x40;
    }
    (*(ScriptFlagState **)0x0200F450)->unknown_51 = 0x30;
    state = *(ScriptFlagState **)0x0200F450;
    state->current = state->entries[--state->count];
    state->entries[state->count++] = state->current;
    state->current = 0x42;
    state->entries[state->count++] = state->current;
    state->current = 0x37;
}
