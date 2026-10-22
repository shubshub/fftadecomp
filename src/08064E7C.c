#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x203D];
    u8 field_203d;
    u8 unknown_203e[0x152];
    u8 field_2190;
    u8 field_2191;
    u8 unknown_2192[0x0C];
    u16 field_219e;
    u8 unknown_21a0[0x1A84];
    u32 field_3c24;
    u16 field_3c28;
    u8 field_3c2a;
    u8 unknown_3c2b[0x7D];
} BackupState;

typedef struct {
    u8 unknown_000[0x88C];
    BackupState snapshot;
} BackupScriptState;

extern u8 g_state_02000000[];

void func_080C960C(u16 bit_index, u16 enabled, void *base);

void func_08064E7C(void)
{
    BackupScriptState *initial = *(BackupScriptState **)0x0200F450;
    BackupState *snapshot = &initial->snapshot;

    ((void (*)(void *, void *, s32))*(u32 *)0x0836D4BC)
        (snapshot, g_state_02000000, 0x3CA8);
    initial->snapshot.field_2191 = initial->snapshot.field_2190;
    initial->snapshot.field_219e = 0;
    initial->snapshot.field_3c28 = 0;
    initial->snapshot.field_3c2a = 0;
    initial->snapshot.field_3c24 = 0;
    initial->snapshot.field_203d = 0;
    func_080C960C(0x40, 0, snapshot);
}
