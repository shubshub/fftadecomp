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

typedef struct ScriptSignal {
    u8 unknown_00[2];
    u16 identifier;
    u16 value;
} ScriptSignal;

typedef struct ScriptInput {
    u8 flags;
    u8 unknown_01;
    u8 kind;
    u8 unknown_03[0x11D];
    u16 field_120;
    u16 field_122;
    u8 field_124;
} ScriptInput;

void func_08064508(void)
{
    ExtendedScriptState **state_slot = (ExtendedScriptState **)0x0200F450;
    ExtendedScriptState *state = *state_slot;
    ScriptSignal *outgoing;
    ScriptSignal *incoming;
    ScriptInput *input;

    if (!(state->flags & 0x10)) {
        state->flags &= ~0x20;
        state->current = state->entries[--state->count];
        return;
    }
    state->values[1] = 0;
    state->values[0] = 0;
    outgoing = (ScriptSignal *)0x03002B50;
    outgoing->value = 0;
    outgoing->identifier = 0;
    incoming = (ScriptSignal *)0x03002890;
    incoming->value = 0;
    incoming->identifier = 0;
    input = (ScriptInput *)0x030028A0;
    if (input->field_124 != 1) {
        if (input->field_120 != 0 || (input->field_122 > 200 && input->kind != 3)) {
            if (state->flags & 0x20) {
                ExtendedScriptState *resume;

                state->flags &= ~0x20;
                state->field_52 = 0xFF;
                resume = *state_slot;
                resume->current = resume->entries[--resume->count];
            } else {
                state->current = 0x44;
                state->entries[state->count++] = 0x44;
                state->current = 0x34;
                state->entries[state->count++] = 0x34;
                state->current = 0x36;
            }
        }
    } else {
        ExtendedScriptState *resume;

        state->values[!(input->flags & 8)] = state->field_66;
        state->unknown_51 = 0x10;
        resume = *state_slot;
        resume->current = 0x3A;
    }
}
