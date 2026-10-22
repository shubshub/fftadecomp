#include "ffta.h"

typedef struct ScriptFlagState {
    u16 current;
    u16 count;
    u16 entries[34];
    u8 unknown_48[5];
    u8 unknown_4d;
    u16 field_4e;
    u8 unknown_50;
    u8 unknown_51;
    u8 unknown_52[2];
    u32 flags;
} ScriptFlagState;

void func_08029E48(void *owner, u32 unused, u16 *scratch,
                   s16 column, s16 row, u8 enabled);

void func_08064BC4(void)
{
    ScriptFlagState *state;

    if ((*(ScriptFlagState **)0x0200F450)->flags & 1) {
        func_08029E48((void *)0x030008B0, 0, 0, 0x14, 0x10, 1);
    } else {
        func_08029E48((void *)0x030008B0, 0, 0, 0x14, 0x10, 0);
    }
    state = *(ScriptFlagState **)0x0200F450;
    state->current = state->entries[--state->count];
}
