#include "ffta.h"

typedef struct {
    u8 field_00;
    u8 field_01;
    u8 field_02;
    u8 unknown_03;
} Entry08009A14;

typedef struct {
    u8 unknown_0000[0x2192];
    u16 current;
    u8 unknown_2194[0x3C2A - 0x2194];
    u8 index;
} State08009A90;

extern State08009A90 g_state_02000000;

const Entry08009A14 *func_08009A14(u16 index);

/* 0x08009A90..0x08009AFC: 108 bytes, 45 instructions; literals at 0x08009AE8.
 * State +0x2192 is the current event (08009FD0) and +0x3C2A the selected
 * entry index (081253CC, 08123BC8). */
u16 func_08009A90(u16 value)
{
    u16 slot;

    if ((value & 0xFF) >= 0xF0)
        return (value - 0xF0) & 0xFF;
    if (func_08009A14(g_state_02000000.current)->field_02 == 0x3D) {
        slot = g_state_02000000.index;
        if (slot != 0)
            slot--;
        slot %= 10;
        return value + slot * 24;
    }
    return value;
}
