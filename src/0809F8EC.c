#include "ffta.h"

typedef struct {
    u8 unknown_00[0xD0];
    s16 value;
    u8 unknown_D2[2];
    u16 field_D4;
} State0809F8EC;

extern u8 func_080C9540(u16 bit_index);

/* 0x0809F8EC..0x0809F938:
 * 70 B5 05 1C 2E 1C D0 36 00 20 34 5E 0D 48 24 18
 * 03 20 29 F0 1F FE 00 06 00 28 00 D0 C8 3C 04 20
 * 29 F0 18 FE 00 06 00 28 01 D0 07 48 24 18 00 2C
 * 00 DA 00 24 29 1C D4 31 00 20 08 80 34 80 70 BC
 * 01 BC 00 47 0C FE FF FF D4 FE FF FF. */
void func_0809F8EC(State0809F8EC *state)
{
    s32 value = state->value;

    value -= 500;
    if (func_080C9540(3))
        value -= 200;
    if (func_080C9540(4))
        value -= 300;
    if (value < 0)
        value = 0;
    state->field_D4 = 0;
    state->value = value;
}
