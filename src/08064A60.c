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

typedef struct BackupScriptState {
    u16 current;
    u16 count;
    u16 entries[34];
    u8 unknown_48[9];
    u8 delay;
    u8 result;
    u8 unknown_53[0x99];
    void (*callback)(u32);
    u8 unknown_f0[0x79C];
    BackupState snapshot;
} BackupScriptState;

extern u8 g_state_02000000[];

void func_080C960C(u16 bit_index, u16 enabled, void *base);
u32 func_0813B0D4(u8 selector, void *buffer);

void func_08064A60(void)
{
    BackupScriptState *initial = *(BackupScriptState **)0x0200F450;
    BackupScriptState *state;

    if (initial->result == 0xFF) {
        BackupState *snapshot = &initial->snapshot;

        func_0813B0D4((u8)(g_state_02000000[0x72] - 1), snapshot);
        (*(BackupScriptState **)0x0200F450)->result = 0;
        ((void (*)(void *, void *, s32))*(u32 *)0x0836D4BC)(
            g_state_02000000 + 0x80, (u8 *)snapshot + 0x80, 0x18C0);
        ((void (*)(void *, void *, s32))*(u32 *)0x0836D4BC)(
            g_state_02000000 + 0x1940, (u8 *)snapshot + 0x1940, 0x5A4);
        ((void (*)(void *, void *, s32))*(u32 *)0x0836D4BC)(
            g_state_02000000 + 0x1EE4, (u8 *)snapshot + 0x1EE4, 0x38);
        ((void (*)(void *, void *, s32))*(u32 *)0x0836D4BC)(
            g_state_02000000 + 0x2B08, (u8 *)snapshot + 0x2B08, 0x100);
    } else if (initial->callback) {
        BackupState *backup = (BackupState *)0x02003CB0;

        initial->callback(1);
        (*(BackupScriptState **)0x0200F450)->callback = 0;
        ((void (*)(void *, void *, s32))*(u32 *)0x0836D4BC)(
            backup, g_state_02000000, 0x3CA8);
        backup->field_2191 = backup->field_2190;
        backup->field_219e = 0;
        backup->field_3c28 = 0;
        backup->field_3c2a = 0;
        backup->field_203d = 0;
        func_080C960C(0x40, 0, backup);
        (*(BackupScriptState **)0x0200F450)->result =
            func_0813B0D4((u8)(g_state_02000000[0x72] - 1), backup);
    }
    (*(BackupScriptState **)0x0200F450)->delay = 0x40;
    state = *(BackupScriptState **)0x0200F450;
    state->current = state->entries[--state->count];
}
