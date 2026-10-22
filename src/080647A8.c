#include "ffta.h"

typedef struct ExtendedScriptState {
    u16 current;
    u16 count;
    u16 entries[34];
    u8 unknown_48[5];
    u8 unknown_4d;
    u16 field_4e;
    u8 unknown_50;
    u8 unknown_51;
    u8 field_52;
    u8 unknown_53;
    u32 flags;
    u8 unknown_58[4];
    u32 unknown_5c;
    u8 unknown_60[4];
    u16 field_64;
    u16 field_66;
    u16 values[2];
} ExtendedScriptState;

void func_08141708(void);

void func_080647A8(void)
{
    Record *record = (Record *)0x020020D0;
    ExtendedScriptState *state;
    ExtendedScriptState *resume;
    u8 *signal;

    record->field_0c = 0x19;
    (*(ExtendedScriptState **)0x0200F450)->unknown_4d = 0x0B;
    state = *(ExtendedScriptState **)0x0200F450;
    state->field_64 = 0x9005;
    state->field_66 = 0x1238;
    state->flags |= 0x20;
    state->unknown_51 = 0x20;
    func_08141708();
    signal = (u8 *)0x03000ED0;
    signal[5] = 0;
    resume = *(ExtendedScriptState **)0x0200F450;
    resume->current = 0x3D;
    resume->entries[resume->count++] = resume->current;
    resume->current = 0x37;
    resume->entries[resume->count++] = resume->current;
    resume->current = 0x41;
    resume->entries[resume->count++] = resume->current;
    resume->current = 0x39;
    resume->entries[resume->count++] = resume->current;
    resume->current = 0x40;
    resume->entries[resume->count++] = resume->current;
    resume->current = 0x37;
    resume->entries[resume->count++] = resume->current;
    resume->current = 0x31;
}
