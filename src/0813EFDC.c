#include "ffta.h"

typedef struct {
    u8 active;
    u8 unknown_01;
    s16 x;
    s16 y;
    u8 unknown_06[2];
    s32 fixed_x;
    s32 fixed_y;
    u8 unknown_10[4];
    u16 field_14;
    u16 field_16;
    u8 field_18;
    u8 unknown_19;
    u16 field_1A;
    u16 field_1C;
    u16 field_1E;
    u8 unknown_20;
    u8 field_21;
} State0813EFDC;

typedef struct {
    u8 unknown_00[2];
    s16 y;
} Source0813EFDC;

void func_0813F1D8(State0813EFDC *state, u8 mode);

/* 0x0813EFDC - 162 bytes. */
void func_0813EFDC(State0813EFDC *state, Source0813EFDC *source,
                   u16 x, u16 first, u16 second, u16 third, u8 flag,
                   u16 duration, u8 mode, u8 value)
{
    state->active = 1;
    func_0813F1D8(state, mode);
    state->x = x;
    state->y = source->y;
    state->field_16 = first;
    state->field_14 = second;
    state->field_1E = duration;
    state->field_1A = duration;
    state->field_1C = third;
    state->field_21 = value;
    state->field_18 = flag;
    state->fixed_x = state->x * 256;
    state->fixed_y = state->y * 256;
}
