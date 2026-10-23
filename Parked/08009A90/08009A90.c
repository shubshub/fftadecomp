#include "ffta.h"

typedef struct {
    u8 field_00;
    u8 field_01;
    u8 field_02;
    u8 unknown_03;
} Entry08009A14;

const Entry08009A14 *func_08009A14(u16 index);

/* Target: 0x08009A90..0x08009AFC, including internal literals and return tail. */
u16 func_08009A90(u16 value)
{
    u8 *state;
    u16 counter;

    if ((u8)value > 239)
        return (u8)(value - 240);
    state = (u8 *)0x02000000;
    if (func_08009A14(*(u16 *)(state + 0x2192))->field_02 != 61)
        return value;
    counter = state[0x3C2A];
    if (counter != 0)
        counter--;
    counter = (u16)((u32)counter % 10);
    return value + 24 * counter;
}
