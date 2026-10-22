#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x203D];
    u8 field_203d;
    u8 unknown_203e[0x152];
    u8 field_2190;
    u8 field_2191;
    u8 unknown_2192[0x0C];
    u16 field_219e;
    u8 unknown_21a0[0x1A88];
    u16 field_3c28;
    u8 field_3c2a;
    u8 unknown_3c2b[0x7D];
} BackupState;

extern u8 g_state_02000000[];

void func_080C960C(u16 bit_index, u16 enabled, void *base);
u32 func_0813B0D4(u8 selector, void *buffer);

void func_080649A4(void)
{
    BackupState *backup = (BackupState *)0x02003CB0;
    ScriptState *state;

    ((void (*)(void *, void *, s32))*(u32 *)0x0836D4BC)
        (backup, g_state_02000000, 0x3CA8);
    backup->field_2191 = backup->field_2190;
    backup->field_219e = 0;
    backup->field_3c28 = 0;
    backup->field_3c2a = 0;
    backup->field_203d = 0;
    func_080C960C(0x40, 0, backup);
    (*(ScriptState **)0x0200F450)->unknown_52[0] =
        func_0813B0D4((u8)(g_state_02000000[0x72] - 1), backup);
    (*(ScriptState **)0x0200F450)->unknown_51 = 0x20;
    state = *(ScriptState **)0x0200F450;
    state->current = state->entries[--state->count];
    state->entries[state->count++] = state->current;
    state->current = 0x37;
}
