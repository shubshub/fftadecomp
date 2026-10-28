#include "ffta.h"

/* Complete [0x0813EE20, 0x0813EEF8): 216 bytes, 105 instructions. */
typedef struct {
    u8 active;
    u8 unknown_01[0x20];
    u8 mode;
    u8 unknown_22[2];
} Record0813EE20;

typedef struct {
    u8 mode;
    u8 unknown_01;
    u16 value;
    u8 count;
    u8 unknown_05;
    u16 first;
    u16 second;
    u8 unknown_0A;
    u8 setting_b;
    u8 setting_c;
    u8 setting_d;
    u8 setting_e;
    u8 unknown_0F;
    u16 position[4];
    Record0813EE20 records[125];
    u32 value_11ac;
    u16 count_11b0;
    u8 unknown_11B2[2];
    u32 position_11b4;
    u8 active;
} State0813EE20;

extern void func_0814186C(const void *, void *, u32);

void func_0813EE20(State0813EE20 *state, const u16 *position,
                   u8 record_mode, u16 value, u8 count, u8 setting_c,
                   u8 setting_d, u8 setting_b, u8 setting_e, u8 mode,
                   u16 first, u16 second)
{
    u8 i;

    func_0814186C(position, state->position, 4);
    state->setting_b = setting_b;
    state->setting_c = setting_c;
    state->setting_d = setting_d;
    state->setting_e = setting_e;
    state->mode = mode;
    state->first = first;
    state->second = second;
    state->value = value;
    state->count = count;
    state->active = 0;
    for (i = 0; i < state->count; i++) {
        state->records[i].active = 0;
        state->records[i].mode = record_mode;
    }
}
