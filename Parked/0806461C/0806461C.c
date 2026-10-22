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

void func_0806461C(void)
{
    ScriptInput *input = (ScriptInput *)0x030028A0;
    ExtendedScriptState **state_slot = (ExtendedScriptState **)0x0200F450;
    ScriptSignal *incoming;
    ScriptSignal *outgoing;
    ExtendedScriptState *state;

    if (input->field_120 != 0 || (input->field_122 > 20 && input->kind != 3)) {
        state = *state_slot;
        if (state->flags & 0x20) {
            state->flags &= ~0x20;
            state->field_52 = 0xFF;
            state = *state_slot;
            state->current = state->entries[--state->count];
            return;
        }
        state->current = 0x44;
        state->entries[state->count++] = 0x44;
        state->current = 0x34;
        state->entries[state->count++] = 0x34;
        state->current = 0x36;
    }
    incoming = (ScriptSignal *)0x03002890;
    state = *state_slot;
    if (incoming->identifier == state->field_64) {
        u8 selected = input->flags & 8;

        state->values[selected != 0] = incoming->value;
    }
    state = *state_slot;
    if (state->values[0] == state->field_66 && state->values[1] == state->values[0]) {
        if (state->unknown_51 == 0) {
            state->values[1] = 0;
            state->values[0] = 0;
            outgoing = (ScriptSignal *)0x03002B50;
            outgoing->value = 0;
            outgoing->identifier = 0;
            incoming->value = 0;
            incoming->identifier = 0;
            state->current = state->entries[--state->count];
            state->flags &= ~0x20;
            return;
        }
        state->unknown_51--;
    }
    input->field_124 = 0x16;
    outgoing = (ScriptSignal *)0x03002B50;
    state = *state_slot;
    outgoing->identifier = state->field_64;
    outgoing->value = state->values[!(input->flags & 8)];
}
