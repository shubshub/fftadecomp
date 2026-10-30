#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u8 x;
    u8 y;
    u8 unknown_12[0x6A];
    void *item;
    void *context;
    u8 unknown_84[0x1000];
    u8 field_1084;
    u8 field_1085;
    u8 field_1086;
    u8 field_1087;
    u8 field_1088;
    u8 unknown_1089;
    u8 field_108A;
    u8 field_108B;
} State;

extern void func_08029D48(u8 x, u8 y, u8 value, u8 mode);
extern void *func_08021618(void *context, void *item, u32 zero, u32 mode,
                           u32 first, u32 second, u32 last);

/* 0x08029C34..0x08029CD8 - 164 bytes including literal pool. */
void func_08029C34(State *state, u8 value, u8 first, u8 second,
                   u8 fourth, u8 fifth, u8 sixth)
{
    u8 y;

    state->field_108A = value;
    state->field_1085 = first;
    state->field_1086 = second;
    state->field_1088 = sixth;
    state->field_1087 = fourth;
    state->field_1084 = fifth;

    y = state->field_108B - 7;
    func_08029D48(state->x, (u8)(y + state->y), state->field_108A, 13);
    state->item = func_08021618(state->context, state->item, 0, 20,
                               state->field_1085, state->field_1086, 0);
}
